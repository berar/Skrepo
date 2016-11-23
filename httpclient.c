#include "httpclient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

static int initialized = 0;
const char* USER_AGENT = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0";

static size_t getResourceCallBack(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct HTMLContent *mem = (struct HTMLContent *)userp;

  mem->document = realloc(mem->document, mem->size + realsize + 1);
  if(mem->document == NULL) {
    /* out of document! */
    printf("not enough document (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->document[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->document[mem->size] = 0;

  return realsize;
}

static HTMLContent createErrorHTMLContent() {
    HTMLContent result;
    result.document = "ERROR";
    result.size -1;
    return result;
}

HTMLContent getHTMLContent(char* url) {
    if (!initialized)
        return createErrorHTMLContent();

    CURL *curl_handle;
    CURLcode res;

    HTMLContent result;
    result.document = malloc(1);  // porasce po potrebi preko realloc.
    result.size = 0;

    // Inicijalizacija curl sesije.
    curl_handle = curl_easy_init();
    // Definisanje url-a.
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    // Svi podaci se prosledjuju getResourceCallBack funkciji.
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, getResourceCallBack);
    // Prebacivanje strukture funkciji.
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&result);
    // Dodavanje UserAgent hedera.
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, USER_AGENT);

    res = curl_easy_perform(curl_handle);
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() propao za url %s: %s\n",
                url, curl_easy_strerror(res));
        result = createErrorHTMLContent();
    }

    curl_easy_cleanup(curl_handle);
    return result;
}

void initHTTPClient() {
    if (initialized)
        return;

    curl_global_init(CURL_GLOBAL_ALL);
    initialized = 1;
}
