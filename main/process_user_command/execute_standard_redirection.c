#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../helpers/handle_error/handle_error.h"

void execute_standard_redirection(char **command, int *size_of_command, char **path, int *size_of_path)
{
    char *file_name = command[(*size_of_command) - 1];
    int file_descriptor = open(file_name, O_RDONLY);

    command[(*size_of_command) - 2] = '\0';

    if (file_descriptor == -1)
    {
        printf("file descriptor\n");
        handle_error();
    }
    else
    {

        if (dup2(file_descriptor, STDIN_FILENO) == -1)
        {
            printf("dup2\n");
            handle_error();
        }
        else
        {

            for (int directory_index = 0; directory_index < *size_of_path; directory_index++)
            {
                int nbr_of_fail = 0;

                // Creating path for command to execute
                char *dir_for_command = malloc((strlen(path[directory_index]) + strlen(command[0])) * sizeof(char *));
                strcat(strcat(dir_for_command, path[directory_index]), command[0]);

                // Trying to exec the command
                nbr_of_fail += execv(dir_for_command, command);
                free(dir_for_command);
            }
            for (int i = 0; i < (*size_of_command); i++)
            {
                free(command[i]);
            }
            free(command);
            close(file_descriptor);
        }
    }
}