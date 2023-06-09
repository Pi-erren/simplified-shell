#ifndef PROCESS_USER_COMMAND
#define PROCESS_USER_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>

#include "../helpers/handle_error/handle_error.h"

#include "process_redirection.h"
#include "execute_input_redirection.h"
#include "execute_output_redirection.h"
#include "execute_normal_command.h"

void process_user_command(char **path, char **words, int *size_of_path, int *token_count)
{
    // Process input to detect redirection and adapt the array of command
    int size_of_command = 0;
    bool input_redirection = false;
    bool output_redirection = false;
    char **command = process_redirection(words, token_count, &size_of_command, &input_redirection, &output_redirection);

    int child_pid = fork();

    if (child_pid == 0)
    {
        // Case 1: input redirection
        if (input_redirection)
        {
            execute_input_redirection(command, &size_of_command, path, size_of_path);
        }

        // Case 2: output redirection
        if (output_redirection)
        {
            execute_output_redirection(command, &size_of_command, path, size_of_path);
        }

        // Case 3: normal command
        else
        {
            execute_normal_command(path, words, size_of_path);
        }
    }

    // Parent process
    else
    {
        wait(NULL);
    }
}

#endif