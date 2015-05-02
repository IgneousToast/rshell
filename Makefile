COMPILE = g++
FLAG = -Wall -Werror -ansi -pedantic
all: rshell ls cp
	#mkdir -p ./bin
	#$(COMPILE) $(FLAG) ./src/main.cpp -o ./bin/rshell
	
rshell:
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/main.cpp -o ./bin/rshell
ls:
	@mkdir -p bin
	$(CC) $(FLAGS) src/ls.cpp -o bin/ls
cp: 
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/cp.cpp -o ./bin/cp

clean:
	rm -rf ./bin

