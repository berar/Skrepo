#include <stdio.h>
#include <windows.h>

#define MAX_LINES 1024
#define MAX_LINE_LEN 256
#define RES_FILE_NAME "resources.txt"

FILE* resFile;
char* resources[MAX_LINES];
int resCnt = 0, rateLmt = 0;

char* copy(char* in) {
    char* res = malloc(sizeof(char) * strlen(in));
    strcpy(res, in);
    return res;
}

void initResources() {
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), resFile) && resCnt < MAX_LINES) {
        resources[resCnt++] = copy(line);
    }
    resources[resCnt] = '\0';
    fclose(resFile);
}

void try2InitRateLmt(int argc, char* val) {
    if (argc != 2) {
        printf("Provide rate limiting value in seconds as first argument.");
        exit(-1);
    }
    rateLmt = atoi(val) * 1000;
}

void try2InitResFile() {
    resFile = fopen(RES_FILE_NAME, "r");
    if (resFile == NULL) {
        printf("%s not loaded.", RES_FILE_NAME);
        exit(-1);
    }
}

void init(int argc, char** argv) {
    try2InitRateLmt(argc, argv[1]);
    try2InitResFile();
    initResources();
}

void loop() {
    Sleep(rateLmt);
    printf("OK\n");
    loop();
}

int main(int argc, char** argv)
{
    init(argc, argv);
    loop();
    return 0;
}
