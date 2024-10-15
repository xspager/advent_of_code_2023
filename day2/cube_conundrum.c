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

int is_game_possible(int totals[3])
{
    // only 12 red cubes, 13 green cubes, and 14 blue cubes
    return (totals[RED] <= 12 && totals[GREEN] <= 13 && totals[BLUE] <= 14);
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
        int is_game_possible_flag = 0;

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
            is_game_possible_flag = is_game_possible(totals);
            if (!is_game_possible_flag) break;

            hand_blocks = strtok_r(NULL, ";", &hand_blocks_saveptr);
        }
        if (is_game_possible_flag) {
            sum += game_id;
        }

        //printf("\n");

        line = strtok_r(NULL, "\n", &file_saveptr);
    }

    printf("Sum = %i\n", sum);
    return EXIT_SUCCESS;
}
