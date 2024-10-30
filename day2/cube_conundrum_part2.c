#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <assert.h>

#include "../day1/utils.h"

enum {
    RED = 0,
    GREEN,
    BLUE
};

/*
 * What is the minimal number of cubes of each color to make a game possible?
 *
 * For all hands in each game we need to know what was the largest number of
 * cubes of each color to make all hands possible.
 *
 */

void update_totals(int *totals, int hand[3])
{
    for (int i = 0; i < 3; i++) {
        if (hand[i] > totals[i]) {
            totals[i] = hand[i];
        }
    }
}

#define FANCY

#ifdef FANCY
int mul(int *numbers, int length) {
    if (length == 0) return 0;
    if (length == 1) return numbers[0];

    return numbers[0] * mul(numbers + 1, length - 1);
}
#else
int mul(int *numbers, int length) {
    int tmp;

    tmp = numbers[0];

    for (int i = 1; i < length; i++) {
        tmp *= numbers[i];
    }
    return tmp;
}
#endif

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

    char *file, *line;
    char *file_saveptr, *line_saveptr, *hand_blocks_saveptr, *hand_saveptr;

    int game_id;
    char *hands;

    file = map_file(fd);

    line = strtok_r(file, "\n", &file_saveptr);

    while(line != NULL) {
        //printf("%s\n", line);

        char *game_id_str = strtok_r(line, ":", &line_saveptr);
        sscanf(game_id_str, "%*s %d", &game_id);
        hands = strtok_r(NULL, ":", &line_saveptr);
        //printf("%s\n", hands);

        char *hand_blocks = strtok_r(hands, ";", &hand_blocks_saveptr);

        int count = 0;
        char color[8];
        int min_numbers[3] = {0};

        while(hand_blocks != NULL) {
            int totals[3] = {0};
            char *hand = strtok_r(hand_blocks, ",", &hand_saveptr);

            while (hand != NULL) {
                //printf("%s|", hand);
                sscanf(hand, "%u %s", &count, color);
                if (strcmp("red", color) == 0) totals[RED] += count;
                if (strcmp("green", color) == 0) totals[GREEN] += count;
                if (strcmp("blue", color) == 0) totals[BLUE] += count;

                hand = strtok_r(NULL, ",", &hand_saveptr);
            }

            update_totals(min_numbers, totals);

            hand_blocks = strtok_r(NULL, ";", &hand_blocks_saveptr);
        }

        int power = mul(min_numbers, sizeof(min_numbers) / sizeof(int));
        printf("R: %d, G: %d, B: %d, power = %d\n", min_numbers[RED], min_numbers[GREEN], min_numbers[BLUE], power);
        sum += power;

        //printf("\n");

        line = strtok_r(NULL, "\n", &file_saveptr);
    }

    printf("Sum = %i\n", sum);
    return EXIT_SUCCESS;
}
