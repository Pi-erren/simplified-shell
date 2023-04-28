#ifndef PROCESS_CD_COMMAND
#define PROCESS_CD_COMMAND

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h> // For constant PATH_MAX that gives the length of the string
                    // for the current directory path so we can allocate location_dir dynamically

#define PATH_MAX 4096

char *process_cd_command(char **words)
{
    char *location_dir = malloc(PATH_MAX * sizeof(char *));
    chdir(words[1]);

    getcwd(location_dir, PATH_MAX);
    printf("location dir: %s\n", location_dir);
    return location_dir;
}

#endif