#ifndef PROCESS_USER_COMMAND
#define PROCESS_USER_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../handle_error/handle_error.h"

void process_user_command(char **path, char **words, int *size_of_path, int *token_count)
{
    int a = fork();

    if (a == 0)
    {
        int nbr_of_fail = 0;

        for (int directory = 0; directory < *size_of_path; directory++)
        {
            // Creating path for command to execute
            char *dir_for_command = malloc(strlen(path[directory]) + strlen(words[1]) * sizeof(char *));
            strcat(strcat(dir_for_command, path[directory]), words[1]);

            // Adapting words for execv command
            words[0] = malloc(strlen(dir_for_command) * sizeof(char));
            words[0] = dir_for_command;

            // Trying to exec the command
            nbr_of_fail += execv(words[0], words);
        }

        if (nbr_of_fail == (-1 * (*size_of_path)))
        {
            handle_error();
        }
    }

    // Parent process
    {
        waitpid(a, NULL, 0);
    }
}

#endif