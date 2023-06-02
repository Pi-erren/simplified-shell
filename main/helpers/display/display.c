#ifndef DISPLAY
#define DISPLAY

#include <stdio.h>
#include <string.h>

void display(char *location_dir)
{
    printf("\033[0;32mdash\033[0;37m:\033[0;34m%s\033[0;37m >", location_dir);
}
#endif