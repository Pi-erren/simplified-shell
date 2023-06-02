#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char **process_redirection(char **words, int *token_count, int *size_of_command, bool *is_redirection)
{
    char **new_words;

    // Search for redirection
    for (int i = 0; i < (*token_count); i++)
    {
        char *curr_word = words[i];
        for (int j = 0; j < strlen(curr_word); j++)
        {
            // if we find redirection symnol
            if (curr_word[j] == '<')
            {
                *is_redirection = true;

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
                    (*size_of_command) = (*token_count) + size_of_redirection_array - 1;

                    new_words = malloc((*size_of_command) * sizeof(char *));

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

                    if (index_of_symbol == strlen(words[i]) - 1)
                    {
                        new_words[(*size_of_command) - 1] = malloc(strlen(words[(*token_count) - 1]) + 1);
                        strcpy(new_words[(*size_of_command) - 1], words[(*token_count) - 1]);
                    }
                    // free redirection array
                    for (int i = 0; i < size_of_redirection_array; i++)
                    {
                        free(redirection_array[i]);
                    }
                    free(redirection_array);
                    return new_words;
                }
                (*size_of_command) = (*token_count);
                return words;
            }
        }
    }
    (*size_of_command) = (*token_count);
    return words;
}
