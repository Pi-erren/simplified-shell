#ifndef PROCESS_INPUT
#define PROCESS_INPUT

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char **init_path()
{
    char **path = malloc(2 * sizeof(char *)); // path is an array of dictionaries where dash search for commands to exec
    path[0] = malloc(strlen("/bin/") + 1);
    strcpy(path[0], "/bin/"); // We give it a default directory for commands
    path[1] = NULL;

    return path;
}
#endif