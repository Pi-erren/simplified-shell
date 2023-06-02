# I - Compile and Launch
## Compile
go to root directory
in terminal: 
```
chmod +x compile.sh
```
```
./compile.sh
```
## Launch
* Warning: any command line argument will lead to an error
```
./dash
```

# II - Dash-specific commands and available functionalities
## Dash-specific commands
### path
* path arguments represent directories where the shell will search for executables
* path takes an unlimited quantity of arguments
* path default value is /bin/
* example: path /home/my_pc /bin/usr/  
    shell will then loop through the directories and execute the command
    in the first directory where he finds the command

* set up path:
```shell
path [path_to_directoy_1] ... [path_to_directory_n]
```

* display actual path array:
```shell
path
```
### Functionalities
* Dash can handle standard redirection '<'

si erreur getline pas déclaré
il faut rajouter:
#define _GNU_SOURCE

-Wall -Wextra -Werror -std=c17