#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINES 1024
#define MAX_LINE_LEN 256
#define SEC2MILIS 1000 * 1000
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
        strtok(line, "\r\n");
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
    rateLmt = atoi(val) * SEC2MILIS;
}

void try2InitResoures() {
    resFile = fopen(RES_FILE_NAME, "r");
    if (resFile == NULL) {
        printf("%s not loaded.", RES_FILE_NAME);
        exit(-1);
    }
    initResources();
}

void init(int argc, char** argv) {
    try2InitRateLmt(argc, argv[1]);
    try2InitResoures();
    system("mkdir -p rfiles");
}

char* getTimestamp() {
    int ts = (unsigned)time(NULL);
    char res[11];
    sprintf(res, "%d", ts);
    return copy(res);
}

char* concat(const char *s1, const char *s2) {
    char *res = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(res, s1);
    strcat(res, s2);
    return res;
}

void replace(char* s, char oldC, char newC) {
    int j = 0;
    while (s[j] != '\0') {
        s[j] = s[j] == oldC ? newC : s[j];
        j++;
    }
}

int loop() {
    usleep(rateLmt);
    int i;
    for (i = 0; i < resCnt; i++) {
        char* ts = getTimestamp();
        char* fileName = concat(resources[i], ts);
        replace(fileName, '/', '.');
        char* filePath = concat("./rfiles/", fileName);
        char* cmdPref = concat("wget --quiet -O ", filePath);
        char* cmdSuff = concat(" - ", resources[i]);
        char* cmd = concat(cmdPref, cmdSuff);
        system(cmd);

        char* resCpy = copy(resources[i]);
        replace(resCpy, '/', '.');
        //char* filePathPref = concat("./rfiles/", resCpy);

        char* cmpCmdPref = "ls ./rfiles | grep ";
        char* cmpCmdInf = concat(resCpy, " | tail -2 | head -1 | diff - ");
        char* cmpCmdSuff = concat(filePath, " | wc");
        char* cmpCmd = concat(concat(cmpCmdPref, cmpCmdInf), cmpCmdSuff);
        system(cmpCmd);
        //printf("%s\n", cmpCmd);
    }
    return loop();
}

int main(int argc, char** argv) {
    init(argc, argv);
    return loop();
}
