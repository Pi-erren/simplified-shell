#ifndef PROCESS_PATH_COMMAND
#define PROCESS_PATH_COMMAND

// Function to process the command path
// Consists in overwritting previous path array with new one with given input arguments
// Prints actual path if no arguments
char **process_path_command(char **words, int *token_count, int *size_of_path, char **path);

#endif