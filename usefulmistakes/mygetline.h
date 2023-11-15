#ifndef MY_GETLINE_H
#define MY_GETLINE_H

#include <unistd.h>

/* my getline function*/

ssize_t mygetline(char **lineptr, size_t *n, int fd);

#endif

