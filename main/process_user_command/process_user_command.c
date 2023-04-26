#ifndef PROCESS_USER_COMMAND
#define PROCESS_USER_COMMAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void process_user_command(char **path, char **words, int *size_of_path, int *token_count)
{
    int pid = fork();
    if (pid < 0)
    {
        printf("echec\n");
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
    else if (pid == 0)
    {

        printf("pid: %d", pid);
        for (int directory = 0; directory < *size_of_path; directory++)
        {
            // Completing path to command and prepare words for execv function
            char *dir_for_command = path[directory];
            strcat(dir_for_command, words[1]);
            words[0] = dir_for_command;

            printf("\nexecv first arg: %s\nexecv second arg: {", words[0]);
            for (int i = 0; i < *token_count; i++)
            {
                printf("words[%s], ", words[*token_count]);
            }
            printf("}\n");

            int error = execv(words[0], words);

            if (error == -1)
            {
                char error_message[30] = "An error has occurred\n";
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
        }
    }
    {
        // Parent process
        waitpid(pid, NULL, 0);
    }
    printf("user command executed\n");
}

#endif