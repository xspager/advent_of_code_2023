#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <assert.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include "utils.h"

#define PATTERN "([0-9]|one|two|three|four|five|six|seven|eight|nine|zero){1}.*(\\g<1>)"

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

    file = map_file(fd);

    PCRE2_SPTR pattern;
    pattern = (PCRE2_SPTR) PATTERN;

    int errorcode = 0;
    PCRE2_SIZE erroroffset = 0;
    pcre2_code *re = pcre2_compile(pattern, strlen(PATTERN), 0, &errorcode, & erroroffset, NULL);

    assert(re != NULL);

    line = strtok(file, "\n");

    pcre2_match_data *match_data;
    PCRE2_SPTR subject;
    size_t subject_len;
    int rc;
    PCRE2_UCHAR8 **buffer;
    PCRE2_SIZE *lenghtsptr;


    while(line != NULL) {
        /*printf("%s\n", line);*/
        match_data = pcre2_match_data_create_from_pattern(re, NULL);
        subject = (PCRE2_SPTR) line;
        subject_len = strlen(line);
        rc = pcre2_match(re, subject, subject_len, 0, 0, match_data, NULL);

        assert(re >= 0);
        pcre2_substring_list_get(match_data, &buffer, &lenghtsptr);
        /*printf("%s %s\n", buffer[1], buffer[2]);*/

        if (lenghtsptr[1] == 1) {
            first_number = buffer[1][0] - '0';
        } else {
            first_number = string_number_to_int(buffer[1]);
        }
        if (lenghtsptr[2] == 1) {
            last_number = buffer[2][0] - '0';
        } else {
            last_number = string_number_to_int(buffer[2]);
        }
        /*printf("=> %i %i\n", first_number, last_number);*/

        printf("%s\t\t\t%s %s => %i\n", line, buffer[1], buffer[2], ((first_number * 10) + last_number));
        sum += ((first_number * 10) + last_number);

        line = strtok(NULL, "\n");
    }

    printf("Calibration values sum = %i\n", sum);
    return EXIT_SUCCESS;
}
