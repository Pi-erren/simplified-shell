#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "process_input/process_input.h"

#include "process_user_command/process_user_command.h"
#include "process_path_command/process_path_command.h"
#include "process_path_command/init_path.h"

#include "process_exit_command/process_exit_command.h"

#include "process_cd_command/process_cd_command.h"
#include "process_cd_command/init_location_dir.h"

#include "helpers/display/display.h"

int main(void)
{

    // Path array initialization
    int size_of_path = 1;
    char **path = init_path();

    // Positioning to default directory "~"
    char *location_dir = init_location_dir();

    while (1)
    {
        printf("\ndirs for commands:\n");
        for (int i = 0; i < size_of_path; i++)
        {
            printf("new path[%d]: %s\n", i, path[i]);
        }

        // Display for shell
        display(location_dir);

        // Processing input
        int token_count = 0;
        char **words = process_input(&token_count);

        // exit command
        if (strcmp(words[0], "exit") == 0)
        {
            process_exit_command(words, &token_count, path, &size_of_path);
        }

        // cd command
        else if (strcmp(words[0], "cd") == 0)
        {
            location_dir = process_cd_command(words);
        }

        // path command
        else if (strcmp(words[0], "path") == 0)
        {
            size_of_path = 0;
            path = process_path_command(words, &token_count, &size_of_path);
        }

        // User command executed with commands from directories in path array
        else
        {
            process_user_command(path, words, &size_of_path, &token_count);
        }
    }
}