#!/bin/bash

gcc main/process_input/process_input.c main/process_path_command/process_path_command.c main/process_path_command/init_path.c main/process_user_command/process_user_command.c main/dash.c main/handle_error/handle_error.c -o dash -Wall

./dash