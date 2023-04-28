#ifndef INIT_LOCATION_DIR
#define INIT_LOCATION_DIR

#include <unistd.h>
#include <stdlib.h>

char *init_location_dir(void)
{
    char *location_dir = malloc(sizeof(char *));
    location_dir = "/home";
    chdir(location_dir);

    return location_dir;
}

#endif