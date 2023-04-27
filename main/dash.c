#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "process_input/process_input.h"
#include "process_user_command/process_user_command.h"
#include "process_path_command/process_path_command.h"
#include "process_path_command/init_path.h"

int main(void)
{

    // Path array initialization
    int size_of_path = 2;
    char **path = init_path();

    chdir("/home");

    while (1)
    {
        printf("\ndirs for commands:\n");
        for (int i = 0; i < size_of_path; i++)
        {
            printf("new path[%d]: %s\n", i, path[i]);
        }
        // Processing input
        int token_count = 0;
        char **words = process_input(&token_count);

        // exit command
        if (strcmp(words[1], "exit") == 0)
        {
            free(words);

            free(path);

            exit(0);
        }

        // cd command
        else if (strcmp(words[1], "cd") == 0)
        {
            chdir(words[1]);
        }

        // path command
        else if (strcmp(words[1], "path") == 0)
        {
            size_of_path = 0;
            path = process_path_command(words, &token_count, &size_of_path);
        }

        // User command executed with commands from directories in path array
        else
        {
            process_user_command(path, words, &size_of_path, &token_count);
        }
    }
}