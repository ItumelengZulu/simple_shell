#include "shell.h"

ssize_t mygetline(char **lineptr, size_t *n, int fd) {
    ssize_t bytesRead;
    size_t pos = 0;

    size_t start;
    size_t length;

    char *newLine;

    if (*lineptr == NULL || *n == 0) {
        *n = 120; /* Set an initial buffer size if not provided */
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1; /* Allocation failure */
        }
    }

    while (1) {
        char buffer[120];
        bytesRead = read(fd, buffer, sizeof(buffer));

        if (bytesRead == -1) {
            return -1; /* Read error */
        }

        start = pos;
        length = pos - start;

        if (pos == (size_t)bytesRead || bytesRead == 0) {
            break; /* End of file or read error */
        }

        /* Allocate or reallocate memory for line */
        newLine = (char *)malloc(length + bytesRead + 1);
        if (newLine == NULL) {
            return -1; /* Allocation failure */
        }

        /* Copy the content from the old line to the new one */
        if (*lineptr != NULL) {
            memcpy(newLine, *lineptr, pos);
            free(*lineptr); /* Remember to free the allocated memory */
        }

        /* Copy the new content to the line */
        memcpy(newLine + pos, buffer, bytesRead);

        *lineptr = newLine;
        *n = length + bytesRead + 1;
    }

    return pos; /* Return the number of characters read */
}