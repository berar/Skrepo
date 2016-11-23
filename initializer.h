#ifndef INITIALIZER_H_INCLUDED
#define INITIALIZER_H_INCLUDED

/**
 * Initialized the program. Passed in programs arguments.
 * First argument is rate limit in seconds given as an integer.
 * Terminates program on error.
 */
void init(int argc, char** argv);

/**
 * Returns rate limit used between scrapes.
 */
int getRateLmt();

#endif // INITIALIZER_H_INCLUDED
