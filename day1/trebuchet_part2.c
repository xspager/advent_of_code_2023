#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

/*#include <pcre2.h>*/

#include "utils.h"

int main()
{
    int fd;
    char *input_file_name = "input";
    int first_number = -1, last_number = -1, calibration_value;
    int sum = 0;

    fd = open(input_file_name, O_RDONLY);

    if(!fd) {
        char *msg_tmpl = "Opening input file \"%s\"";
        char *msg;
        msg = malloc((strlen(msg_tmpl) - 2 + strlen(input_file_name) + 1) *  sizeof(char));
        sprintf(msg, msg_tmpl, input_file_name);
        perror(msg);
        free(msg);
        return EXIT_FAILURE;
    }

    char *file, *line;
    size_t file_length;
    int line_length;

    file = map_file(fd, &file_length);

    printf("file size = %li\n", file_length);

    line = strtok(file, "\n");

    while(line != NULL) {
        printf("%s\n", line);
        line = strtok(NULL, "\n");
    }

    printf("Calibration values sum = %i\n", sum);
    return EXIT_SUCCESS;
}
