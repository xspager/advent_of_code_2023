#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *file;
    const int BUFFER_SIZE = 128;
    char *buffer;
    char *input_file_name = "input";
    int bytes_read;
    int first_number = -1, last_number = -1, calibration_value;
    int i;
    int sum = 0;

    file = fopen(input_file_name, "r");

    if(!file) {
        char *msg_tmpl = "Opening input file \"%s\"";
        char *msg;
        msg = malloc((strlen(msg_tmpl) - 2 + strlen(input_file_name) + 1) *  sizeof(char));
        sprintf(msg, msg_tmpl, input_file_name);
        perror(msg);
        free(msg);
        return EXIT_FAILURE;
    }

    buffer = malloc(BUFFER_SIZE * sizeof(char));

    if(!buffer) {
        perror("Failed to allocate buffer");
        free(buffer);
    }

    while(!feof(file)){
        bytes_read = fread(buffer, sizeof(*buffer), BUFFER_SIZE, file);

        for(i = 0; i < bytes_read; i++){
            if(buffer[i] == '\n') {
                calibration_value = (first_number * 10) + last_number;
                /*
                printf("Calibration value: %i\n", calibration_value);
                */
                sum += calibration_value;
                first_number = -1;
                last_number = -1;
                continue;
            }
            if(isdigit(buffer[i])) {
                if(first_number == -1) first_number = buffer[i] - '0';
                last_number = buffer[i] - '0';
            }
        }
    }
    free(buffer);

    printf("Calibration values sum = %i\n", sum);
    return EXIT_SUCCESS;
}
