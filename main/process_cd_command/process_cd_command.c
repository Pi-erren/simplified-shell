#ifndef PROCESS_CD_COMMAND
#define PROCESS_CD_COMMAND

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *process_cd_command(char **words)
{
    char *dir_for_cd = malloc(strlen(words[1]) + 1);
    dir_for_cd = words[1];
    chdir(dir_for_cd);

    return dir_for_cd;
}

#endif