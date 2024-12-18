#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include "utils.h"

char *map_file(int fd) {
    void *mapped_file = NULL;
    size_t file_length = 0;
    struct stat statbuffer;

    fstat(fd, &statbuffer);
    file_length = statbuffer.st_size;

    mapped_file = mmap(NULL, file_length, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

    if (mapped_file == MAP_FAILED) {
        perror("Failed to map the file to memory");
        return NULL;
    }
    return (char *) mapped_file;
}

int string_number_to_int(char *string_number)
{
    char *value_for_string[10] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    int i;
    int match;
    for(i = 0; i < 10; i++) {
        match = strcmp(value_for_string[i], string_number);
        if (match == 0){
            return i;
        }
    }
    return -1;
}
