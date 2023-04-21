#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "process_input.h"

int main(void)
{
    char *path = "/bin";
    char *curr_dir = '/home';

    while (1)
    {

        // Read input
        char *words[50];
        process_input(words);

        // exit command
        if (strcmp(words[0], "exit") == 0)
        {
            free(words);
            exit(0);
        }

        // cd command
        if (strcmp(words[0], "cd") == 0)
        {
        }

        // path command
        if (strcmp(words[0], "path") == 0)
        {
        }

        // User command executed with commands from the directory of "path"
    }
}
