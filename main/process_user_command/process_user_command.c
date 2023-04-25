#ifndef PROCESS_USER_COMMAND
#define PROCESS_USER_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void process_user_command(char **path, char **words)
{
    char *dir = path[0];

    int pid = fork();

    if (pid == 0)
    {
        strcat(dir, words[0]);

        int x = execv(dir, words);

        if (x == -1)
        {
            printf("Error in executing the command\n");
        }
    }
    {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}

#endif