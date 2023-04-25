#ifndef PROCESS_INPUT
#define PROCESS_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **process_input(int *token_count)
{

    char *input = NULL;   // if input and input_len are initialized to null values,
    size_t input_len = 0; // they will be dynamically malloc

    printf("dash> ");
    getline(&input, &input_len, stdin); // Read user input
    char **words = malloc((input_len + 1) * sizeof(char *));

    // Analyse input words and store them in words array
    char *token = strtok(input, " ");

    while (token != NULL)
    {
        if (*token_count > 0) // with keep index 0 to store the dir where execv will search the command
        {

            words[*token_count] = malloc(strlen(token) + 1);

            strcpy(words[*token_count], token);

            token = strtok(NULL, " ");

            (*token_count)++;
        }
    }

    // Delete the carriage return
    words[*token_count - 1][strcspn(words[*token_count - 1], "\n")] = 0;

    return words;
}

#endif