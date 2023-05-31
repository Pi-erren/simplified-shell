#ifndef PROCESS_USER_COMMAND
#define PROCESS_USER_COMMAND

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include "../helpers/handle_error/handle_error.h"
#include "process_redirection.h"

void process_user_command(char **path, char **words, int *size_of_path, int *token_count)
{
    // Search for redirection
    bool is_redirection = false;

    for (int i = 0; i < (*token_count); i++)
    {
        char *curr_word = words[i];
        for (int j = 0; j < strlen(curr_word); j++)
        {
            // if we find redirection symnol
            if (curr_word[j] == '<')
            {
                is_redirection = true;

                // Find index of symbol in words[i]
                int index_of_symbol;
                char *symbol;
                symbol = strchr(words[i], '<');
                index_of_symbol = (int)(symbol - words[i]);

                // if words[i] is just "<"" (so its len is 1), we don't need to process
                // therefore we process only if >1
                if (strlen(words[i]) > 1)
                {
                    // copy of words[i] because strtok modifies original string
                    char *copy = strdup(words[i]);

                    // Determine in how many elements to split words[i]
                    int size_of_redirection_array;
                    if (index_of_symbol == 0 || index_of_symbol == strlen(words[i]) - 1)
                    {
                        size_of_redirection_array = 2;
                    }
                    else
                    {
                        size_of_redirection_array = 3;
                    }

                    // New elements after splitting
                    char **redirection_array = malloc(size_of_redirection_array * sizeof(char *));

                    // Tokenize words[i]
                    char *token = strtok(copy, "<");
                    int index = 0;
                    while (token != NULL)
                    {
                        if (index_of_symbol == 0 && index < size_of_redirection_array)
                        {
                            redirection_array[index] = strdup("<");
                            index++;
                        }

                        redirection_array[index] = strdup(token);
                        index++;

                        // Add '<' as a separate element
                        if (index < size_of_redirection_array)
                        {
                            redirection_array[index] = strdup("<");
                            index++;
                        }

                        token = strtok(NULL, "<");
                    }

                    // Adapt words
                    printf("index of symbol: %d\n", index_of_symbol);
                    printf("i: %d\n", i);

                    int size_of_new_words = (*token_count) + size_of_redirection_array - 1;
                    printf("size of new words: %d\n", size_of_new_words);

                    char **new_words = malloc(size_of_new_words * sizeof(char *));
                    for (int k = 0; k < i; k++)
                    {
                        new_words[k] = malloc(strlen(words[k]) + 1);
                        new_words[k] = strcpy(new_words[k], words[k]);
                    }

                    int counter1 = 0;
                    for (int k = i; k < i + size_of_redirection_array; k++)
                    {
                        new_words[k] = malloc(strlen(redirection_array[counter1]) + 1);
                        new_words[k] = strcpy(new_words[k], redirection_array[counter1]);
                        counter1++;
                    }
                    // printf("ok\n");
                    new_words[size_of_new_words - 1] = malloc(strlen(words[(*token_count) - 1]) + 1);
                    // printf("size of new words -1: %d\n", size_of_new_words - 1);
                    // printf("last element of new words: %s\n", new_words[size_of_new_words - 1]);

                    // printf("token count: %d\n", (*token_count));
                    // printf("last element of words: %s\n", words[(*token_count) - 1]);

                    if (index_of_symbol == strlen(words[i]) - 1)
                    {
                        new_words[size_of_new_words - 1] = malloc(strlen(words[(*token_count) - 1]) + 1);
                        strcpy(new_words[size_of_new_words - 1], words[(*token_count) - 1]);
                    }
                    for (int i = 0; i < size_of_new_words; i++)
                    {
                        printf("new_words[%d]: %s\n", i, new_words[i]);
                    }
                }
            }
        }
    }
    int child_pid = fork();

    if (child_pid == 0)
    {
        int nbr_of_fail = 0; // count each fail of execv with path directories

        for (int directory = 0; directory < *size_of_path; directory++)
        {
            // Creating path for command to execute
            char *dir_for_command = malloc(strlen(path[directory]) + strlen(words[0]) * sizeof(char *));
            strcat(strcat(dir_for_command, path[directory]), words[0]);

            // Trying to exec the command
            nbr_of_fail += execv(dir_for_command, words);
        }

        if (nbr_of_fail == (-1 * (*size_of_path)))
        {
            handle_error();
        }
    }

    // Parent process
    {
        waitpid(child_pid, NULL, 0);
    }
}

#endif