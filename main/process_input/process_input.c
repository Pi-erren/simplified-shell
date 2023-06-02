#ifndef PROCESS_INPUT
#define PROCESS_INPUT
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **process_input(int *token_count)
{

    char *input = NULL;   // if input and input_len are initialized to null values,
    size_t input_len = 0; // they will be dynamically malloc

    getline(&input, &input_len, stdin); // Read user input
    char **words = malloc((input_len) * sizeof(char *));

    // Analyse input words and store them in words array
    char *token = strtok(input, " ");

    while (token != NULL)
    {
        words[*token_count] = malloc(strlen(token) + 1);

        strcpy(words[*token_count], token);

        token = strtok(NULL, " ");

        (*token_count)++;
    }

    // Delete the carriage return
    words[*token_count - 1][strcspn(words[*token_count - 1], "\n")] = 0;

    return words;
}

#endif