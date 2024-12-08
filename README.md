# Author
* Pierre Neveu, Student at PSL Dauphine University, pierre.neveu@dauphine.eu
* Project obtained the grade of 18/20: developped under Linux Ubuntu
* Course: Operating system
# I - Compile and Launch
**go to root directory**
## Compile
### dash
```
chmod +x compile.sh
```
```
./compile.sh
```
### tests

**please note that some tests required a local path using your local user name, change the variable 'username' at the start of tests.c file according to your local user name so that tests run correctly**
 
in terminal: 
```
chmod +x tests_compile.sh
```
```
./tests_compile.sh
```
## Launch
### dash
* Warning: any command line argument will lead to an error
```
./dash
```
### tests
```
./tests
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
## Functionalities
* Dash can handle standard input '<' and output '>' redirection from and to a file
