#ifndef PROCESS_PATH_COMMAND
#define PROCESS_PATH_COMMAND_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **process_path_command(char **words, int *token_count, int *size_of_path)
{
    char **path = malloc(((*token_count) - 1) * sizeof(char *));

    for (int i = 2; i < (*token_count); i++)
    {
        path[*size_of_path] = malloc(strlen(words[i]) + 1);

        path[*size_of_path] = words[i];

        (*size_of_path)++;
    }

    return path;
}

#endif