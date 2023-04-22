#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "process_input/process_input.h"
#include "user_command/user_command.h"

int main(void)
{
    char *path = malloc(50 * sizeof(char));
    char *curr_dir = malloc(50 * sizeof(char));

    strcpy(path, "/bin/");
    strcpy(curr_dir, "/home");

    chdir(curr_dir);

    while (1)
    {

        // Read input
        char **words = malloc(50 * sizeof(char *));
        process_input(words);

        // exit command
        if (strcmp(words[0], "exit") == 0)
        {
            free(words);
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
        }

        // User command executed with commands from the directory of "path"
        else
        {
            user_command(path, words);
        }
    }
}
