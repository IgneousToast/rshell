all: rshell
	rm -rfv bin
	mkdir bin
	g++ -W -Wall -ansi -pedantic src/main.cpp -o bin/rshell
rshell:
	rm -rfv bin
	mkdir bin
	g++ -W -Wall -ansi -pedantic src/main.cpp -o bin/rshell	
run:
	bin/rshell	
