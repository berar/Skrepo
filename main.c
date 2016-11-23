#include <stdio.h>
#include "urihandler.h"
#include "httpclient.h"

int main(int argc, char **argv)
{
    /*
    resource* resources = (struct resource*) malloc(sizeof(struct resource));
    try2InitURIs(resources);

    int i;
    for (i = 0; i < getURICnt(); i++) {
        printf("%s\n", resources[i].uri);
        printf("%s\n", resources[i].elem.tag);
        printf("%s\n", resources[i].elem.attr.name);
        printf("%s\n", resources[i].elem.attr.value);
    }

    free(resources);
    */

    initHTTPClient();
    printf("%s\n", getHTMLContent("tfzr.rs"));

    return 0;
}
