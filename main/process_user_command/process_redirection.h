#ifndef PROCESS_DIRECTION
#define PROCESS_DIRECTION

// Process when a redirection is detected
// It adapt words by making of < or > a separated element of words
// example:
//      {"a<", "b"} becomes {"a", "<", "b"}
//      {"a", "<b"} becomes {"a", "<", "b"}
//      {"a", "<", "b"} stays {"a", "<", "b"}
char **process_redirection(char **words, int *token_count, int *size_of_command, bool *input_redirection, bool *output_redirection);

#endif