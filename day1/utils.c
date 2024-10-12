#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include "utils.h"

char *map_file(int fd, size_t *length) {
    void *mapped_file = NULL;
    size_t file_length = 0;
    struct stat statbuffer;

    fstat(fd, &statbuffer);
    file_length = statbuffer.st_size;
    *length = file_length;

    mapped_file = mmap(NULL, file_length, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (mapped_file == MAP_FAILED) {
        perror("Failed to map the file to memory");
        return NULL;
    }
    return (char *) mapped_file;
}
