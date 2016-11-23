#ifndef STRINGUTIL_H_INCLUDED
#define STRINGUTIL_H_INCLUDED

/**
 * Returns value copy of in. Doesn't mutate in.
 */
char* copy(char* in);

/**
 * Returns UNIX timestamp at the moment of call.
 */
char* getTimestamp();

/**
 * Returns s1 + s2. Doesn't mutate s1 and s2.
 */
char* concat(const char *s1, const char *s2);

/**
 * Replaces any oldC in s with newC. Case-sensitive. Mutates s.
 */
void replace(char* s, char oldC, char newC);

#endif // STRINGUTIL_H_INCLUDED
