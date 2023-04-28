#ifndef PROCESS_EXIT_COMMAND
#define PROCESS_EXIT_COMMAND

#include <stdlib.h>

void process_exit_command(char **words, int *token_count, char **path, int *size_of_path)
{
    for (int i = 0; i < *token_count + 1; i++)
    {
        free(words[i]);
    }
    free(words);

    for (int i = 0; i < *size_of_path; i++)
    {
        free(path[i]);
    }
    free(path);

    exit(0);
}

#endif