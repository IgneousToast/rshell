COMPILE = g++
FLAG = -Wall -Werror -ansi -pedantic
all: rshell cp
	#mkdir -p ./bin
	#$(COMPILE) $(FLAG) ./src/main.cpp -o ./bin/rshell
	
rshell:
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/main.cpp -o ./bin/rshell
cp: 
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/cp.cpp -o ./bin/cp

clean:
	rm -rf ./bin

