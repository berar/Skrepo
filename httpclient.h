#ifndef HTTPCLIENT_H_INCLUDED
#define HTTPCLIENT_H_INCLUDED

#include <stdlib.h>

typedef struct HTMLContent {
  char* document;
  size_t size;
} HTMLContent;

void initHTTPClient();

// free(chunk.document);
// curl_global_cleanup();
HTMLContent getHTMLContent(char* url);

#endif // HTTPCLIENT_H_INCLUDED
