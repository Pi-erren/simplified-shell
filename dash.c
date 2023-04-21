#include <stdio.h>
#include "read_input.h"
#include <stdlib.h>

int main(void)
{

    // Useful variables
    char **words = malloc(50 * sizeof(char *));
    char *path = malloc(50 * sizeof(char));
    size_t bufsize = 30;
    char *dash = "dash> ";

    // Programme
    while (1)
    {

        // Read user input
        printf("%s", dash);
        getline(&line, &bufsize, stdin);

        // Exit command
        if (line == "exit")
        {
            free(line);
            exit(0);
        }
        // else if ()
        // {
        // }

        printf("%s", line);
    }
}