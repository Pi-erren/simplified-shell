#ifndef HANDLE_ERROR
#define HANDLE_ERROR

#include <unistd.h>
#include <string.h>

void handle_error(void)
{
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

#endif