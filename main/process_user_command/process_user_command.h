#ifndef PROCESS_USER_COMMAND
#define PROCESS_USER_COMMAND

// Processing input of user by separating with spaces
// Returns char **: an array of Strings of the input
// char **[0] is used to store the directory where execv will search for commands
// so that execv will be called like this: execv(words[0], words)
void process_user_command(char **path, char **words, int *size_of_path, int *token_count);

#endif