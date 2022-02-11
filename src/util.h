#ifndef UTIL_H
#define UTIL_H

// Expose the FILE type for simpleGetLine
#include <stdio.h>

// A simplification of getline, that sacrifices
// most of its flexibility for ease of use. It
// simply returns the line read or NULL if the
// original getline enscountered any errors,
// such as reaching EOF. Also the \n gets stripped.
char *simpleGetLine(FILE *stream);

#endif // UTIL_H
