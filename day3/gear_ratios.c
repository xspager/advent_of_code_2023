#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>

#include "../day1/utils.h"

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

#define SYMBOLS "*#+$/%=-@&"

enum MarkersForLine {
    Previous = 0,
    Current
};

void replace(char *str, char *each_of_chars, char replacement)
{
    int i, j;
    for(i=0; i< strlen(str); i++) {
        for(j = 0; j < strlen(each_of_chars); j++) {
            if(str[i] == each_of_chars[j]){
                str[i] = replacement;
            }
        }
    }
}

int lookup(char *str, char c, int start, int end)
{
    int i;
#if 0
    printf("start = %d end = %d\n", start, end);
    printf("%s\n", str);
#endif
    assert(start >= 0 && start < strlen(str));
    assert(end <= strlen(str));
    for (i = start; i <= end; i++) {
        if(str[i] == c) {
            return 1;
        }
    }
    return 0;
}

int sum_line(char *line, char *markers) {
    int sum = 0;
    char *line_with_spaces;

    line_with_spaces = malloc(strlen(line) + 1* sizeof(char));
    strcpy(line_with_spaces, line);

    replace(line_with_spaces, ".", ' '); /* decluter */
#if 1
    /*
     * To make our life easy we replace all symbols for space so they can't be
     * interpreted as sign or part of a number when present afer a digit
     */
    replace(line_with_spaces, SYMBOLS, ' ');
#endif

#if 1
    /*
    printf("%s\n", line);
    printf("%s\n", markers);
    printf("%s\n", line_with_spaces);
    */
#endif
    int start, end;
    char *number_saveptr;
    char *number_str = strtok_r(line_with_spaces, " ", &number_saveptr);
    while (number_str != NULL) {
        /* ignore the tokenized markes by themselves */
        if (isdigit(number_str[0])) {
            /*printf("number \"%s\" = %d\n", number_str, atoi(number_str));*/
            if(!isdigit(number_str[strlen(number_str)-1])){
                printf("%s\n", number_str);
            }
            start = number_str - line_with_spaces;
            end = number_saveptr - line_with_spaces -2;
            /* find a marker adjacent on the markers array */
            if(lookup(markers, '^', MAX(start - 1, 0), MIN(end + 1, strlen(line)))){
                /*printf("%d is adjacent\n", atoi(number_str));*/
                sum += atoi(number_str);
            }
            /*printf("%d %d %d\n", start, end, atoi(number_str));*/
        }
        number_str = strtok_r(NULL, " ", &number_saveptr);
    }

    free(line_with_spaces);

    return sum;
}

int main()
{
    int fd;
    char *input_file_name = "input";
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

    char *file, *line, *previous_line = NULL;
    char *file_saveptr;

    file = map_file(fd);

    char *markers[2] = {NULL};

    line = strtok_r(file, "\n", &file_saveptr);
    while(line != NULL) {
        /* We only want numbers with symbols around on the same line or in the
         * line above or bellow, so we want to store numbers we find without a
         * symbol if there was one adjacent on the previous line or in case
         * there's a symbol in the next
         */
        if(markers[Current] != NULL) {
            if(markers[Previous] != NULL) {
                free(markers[Previous]);
            }
            markers[Previous] = markers[Current];
        }

        markers[Current] = (char *) malloc(strlen(line) + 1 * sizeof(char));
        assert(markers[Current] != NULL);
        memset(markers[Current], ' ', strlen(line));
        /*strcpy(markers[Current], "0123456789");*/


        char *p = strpbrk(line, SYMBOLS);
        while (p) {
            markers[Current][p-line] = '^';
            p = strpbrk(p+1, SYMBOLS);
        }
        markers[Current][strlen(line)] = '\0';

        if (markers[Previous] != NULL) {
            sum += sum_line(line, markers[Previous]);
        }
        sum += sum_line(line, markers[Current]);
        if (previous_line != NULL) {
            sum += sum_line(previous_line, markers[Current]);
        }

        if (previous_line != NULL) {
            free(previous_line);
        }
        previous_line = malloc(strlen(line) + 1 * sizeof(char));
        strcpy(previous_line, line);

        line = strtok_r(NULL, "\n", &file_saveptr);
    }
    free(previous_line);
    free(markers[Previous]);
    free(markers[Current]);

    printf("Sum = %i\n", sum);
    return EXIT_SUCCESS;
}
