#ifndef INIT_LOCATION_DIR
#define INIT_LOCATION_DIR

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *init_location_dir(void)
{
    chdir("/home");

    char *location_dir = malloc(sizeof(char *));
    getcwd(location_dir, sizeof(location_dir));

    return location_dir;
}

#endif