#!/bin/bash

gcc main/process_input/process_input.c main/process_path_command/process_path_command.c main/process_user_command/process_user_command.c main/dash.c -o dash

./dash