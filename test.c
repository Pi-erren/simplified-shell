#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char *input = NULL;
    size_t input_len = 0;
    char **path = NULL;
    int size_of_path = 0;
    char *curr_dir = malloc(50 * sizeof(char));

    chdir(curr_dir);

    while (1)
    {
        // Read user input
        printf("dash> ");
        getline(&input, &input_len, stdin);

        // Allocate memory to an array of strings so that it can store exactly number of words of the user
        // A word is a string surrounded by spaces
        char **words = malloc(input_len * sizeof(char *));

        // Analyse input words and store them in words array
        char *token = strtok(input, " ");

        // Use a pointer because we re use it later;
        int token_count = 0;

        while (token != NULL)
        {
            words[token_count] = malloc(strlen(token) + 1);
            strcpy(words[token_count], token);
            token = strtok(NULL, " ");
            token_count++;
        }

        // Delete the carriage return
        words[token_count - 1][strcspn(words[token_count - 1], "\n")] = 0;

        // exit command

        if (strcmp(words[0], "exit") == 0)
        {
            // Free memory allocated for input and words array
            free(input);

            for (int i = 0; i < token_count; i++)
            {
                free(words[i]);
            }

            free(words);

            for (int i = 0; i < size_of_path; i++)
            {
                free(path[i]);
            }
            free(path);
            exit(0);
        }
        else if (strcmp(words[0], "cd") == 0)
        {
            chdir(words[1]);
        }
        else if (strcmp(words[0], "path") == 0)
        {
            if (path == NULL)
            {
                path = malloc((token_count - 1) * sizeof(char *));
                for (int i = 1; i < token_count; i++)
                {
                    path[i - 1] = malloc(strlen(words[i]) + 1);
                    path[i - 1] = words[i];
                    size_of_path++;
                    // printf("%s", path[i - 1]);
                }
            }
            else
            {
                printf("token_count: %d\n", token_count);
                path = realloc(path, ((size_of_path + token_count - 1) * sizeof(char *)));
                printf("path[%d]: %s", token_count, path[token_count]);
                for (int i = 1; i < token_count; i++)
                {
                    printf("size_of_path: %d\n", size_of_path);
                    path[size_of_path] = malloc(strlen(words[i]) + 1);
                    path[size_of_path] = words[i];
                    size_of_path++;
                }
            }
            for (int i = 0; i < size_of_path; i++)
            {
                printf("%s\n", path[i]);
            }
        }
    }
    // else
    // {
    //     // int pid = fork();
    //     // if (pid == 0)
    //     // {
    //     //     strcat(path, words[0]);
    //     //     int x = execv("path", words);
    //     //     if (x == -1)
    //     //     {
    //     //         printf("Error in executing the command\n");
    //     //     }
    //     // }
    //     // {
    //     //     // Parent process
    //     //     waitpid(pid, NULL, 0);
    //     // }
    // }
    // }
    return 0;
}