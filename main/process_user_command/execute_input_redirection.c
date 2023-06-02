#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../helpers/handle_error/handle_error.h"

void execute_input_redirection(char **command, int *size_of_command, char **path, int *size_of_path)
{
    // Extract file name
    char *file_name = command[(*size_of_command) - 1];

    // Create/open the output file
    int file_descriptor = open(file_name, O_RDONLY);

    // Adapting command array for execv
    command[(*size_of_command) - 2] = '\0';

    if (file_descriptor == -1)
    {
        handle_error();
    }
    else
    {
        // Duplicate the file descriptor to stdin
        if (dup2(file_descriptor, STDIN_FILENO) == -1)
        {
            printf("dup2\n");
            handle_error();
        }
        else
        {
            int nbr_of_fail = 0; // count each fail of execv with path directories

            for (int directory_index = 0; directory_index < *size_of_path; directory_index++)
            {

                // Creating path for command to execute
                char *dir_for_command = malloc((strlen(path[directory_index]) + strlen(command[0])) * sizeof(char *));
                strcat(strcat(dir_for_command, path[directory_index]), command[0]);

                // Trying to exec the command
                nbr_of_fail += execv(dir_for_command, command);
                free(dir_for_command);
            }

            if (nbr_of_fail == (-1 * (*size_of_path)))
            {
                handle_error();
            }

            // Freeing
            for (int i = 0; i < (*size_of_command); i++)
            {
                free(command[i]);
            }
            free(command);
            close(file_descriptor);
        }
    }
}