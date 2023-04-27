#ifndef PROCESS_PATH_COMMAND
#define PROCESS_PATH_COMMAND_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **process_path_command(char **words, int *token_count, int *size_of_path)
{
    char **path = malloc(((*token_count) - 2) * sizeof(char *));

    // Refill of path
    for (int i = 2; i < (*token_count); i++)
    {
        path[*size_of_path] = malloc((strlen(words[i]) + 1));

        char *new_path = words[i];
        strcpy(path[*size_of_path], new_path);

        (*size_of_path)++;
    }

    path[*size_of_path] = NULL;
    (*size_of_path)++;

    return path;
}

#endif