#ifndef USER_COMMAND
#define USER_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void user_command(char *path, char **words)
{
    int pid = fork();
    if (pid == 0)
    {
        strcat(path, words[0]);
        int x = execv(path, words);
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