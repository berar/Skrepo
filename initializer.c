#include "urihandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

#define SEC2MILIS 1000 * 1000

static int rateLmt = 0;

static void try2InitRateLmt(int argc, char* val) {
    if (argc != 2) {
        printf("Provide rate limiting value in seconds as first argument.");
        exit(1);
    }
    rateLmt = atoi(val) * SEC2MILIS;
}

void init(int argc, char** argv) {
    // Inicijalizacija i validacija libxml2.
    LIBXML_TEST_VERSION
    try2InitRateLmt(argc, argv[1]);
//    try2InitURIs();
    system("mkdir -p rfiles");
}

int getRateLmt() {
    return rateLmt;
}
