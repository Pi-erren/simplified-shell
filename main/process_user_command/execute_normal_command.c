#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../helpers/handle_error/handle_error.h"

void execute_normal_command(char **path, char **words, int *size_of_path)
{
    int nbr_of_fail = 0; // count each fail of execv with path directories

    for (int directory_index = 0; directory_index < *size_of_path; directory_index++)
    {
        // Creating path for command to execute
        char *dir_for_command = malloc((strlen(path[directory_index]) + strlen(words[0])) * sizeof(char *));
        dir_for_command = strcat(strcat(dir_for_command, path[directory_index]), words[0]);

        // Trying to exec the command
        nbr_of_fail += execv(dir_for_command, words);

        free(dir_for_command);
    }

    if (nbr_of_fail == (-1 * (*size_of_path)))
    {
        handle_error();
    }
}