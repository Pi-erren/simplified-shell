#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char *input = NULL;
    size_t input_len = 0;
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
            free(words);
            exit(0);
        }

        // cd command
    }
    return 0;
}