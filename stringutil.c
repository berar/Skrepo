#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* copy(char* in) {
    char* res = malloc(sizeof(char) * strlen(in));
    strcpy(res, in);
    return res;
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
