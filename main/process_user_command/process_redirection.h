#ifndef PROCESS_DIRECTION
#define PROCESS_DIRECTION

// Processing input of user by separating with spaces
// Returns char **: an array of Strings of the input
// char **[0] is used to store the directory where execv will search for commands
// so that execv will be called like this: execv(words[0], words)
char **process_redirection(char **words, int *token_count, int *size_of_command, bool *is_redirection);

#endif