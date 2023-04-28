#!/bin/bash

gcc main/process_input/process_input.c main/process_path_command/process_path_command.c main/process_path_command/init_path.c main/process_user_command/process_user_command.c main/dash.c main/helpers/handle_error/handle_error.c main/process_exit_command/process_exit_command.c main/process_cd_command/process_cd_command.c main/process_cd_command/init_location_dir.c main/helpers/display/display.c  -o dash 

./dash