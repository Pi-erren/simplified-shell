#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "process_input/process_input.h"
#include "process_user_command/process_user_command.h"
#include "process_path_command/process_path_command.h"

int main(void)
{
    char **path = malloc(2 * sizeof(char *)); // path is an array of dictionaries where dash search for commands to exec
    path[0] = "/bin/";
    path[1] = NULL;

    while (1)
    {
        int token_count = 0; // Initialize an int to count tokens of input: useful for input processing and path processing

        // Processing input
        char **words = process_input(&token_count);

        // exit command
        if (strcmp(words[0], "exit") == 0)
        {
            free(words);

            free(path);

            exit(0);
        }

        // cd command
        else if (strcmp(words[0], "cd") == 0)
        {
            chdir(words[1]);
        }

        // path command
        else if (strcmp(words[0], "path") == 0)
        {
            free(path);

            int size_of_path = 0; // Initialize an int to count size of path array useful for execv later

            char **path = process_path_command(words, &token_count, &size_of_path);

            for (int i = 0; i < size_of_path; i++)
            {
                printf("path[%d]: %s\n", i, path[i]);
            }
        }

        // User command executed with commands from directories in path array
        else
        {
            process_user_command(path, words);
        }
    }
}