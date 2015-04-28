CC = g++
FLAGS = -g -Wall -Werror -ansi -pedantic 

all: rshell ls

rshell:
	@mkdir -p bin
	$(CC) $(FLAGS) src/main.cpp -o bin/rshell

ls:
	@mkdir -p bin
	$(CC) $(FLAGS) src/ls.cpp -o bin/ls
