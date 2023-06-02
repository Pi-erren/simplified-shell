# Notes
./dash ne doit prendre aucun argument, sinon erreur
# Compile and Launch
go to root directory
in terminal: 
```
chmod +x launch.sh
```

```
./launch.sh
```

# Specific commands available
## path
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

si erreur getline pas déclaré
il faut rajouter:
#define _GNU_SOURCE

-Wall -Wextra -Werror -std=c17