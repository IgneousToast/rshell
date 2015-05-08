COMPILE = g++
FLAG = -Wall -Werror -ansi -pedantic
all: rshell  cp mv rm
	
rshell:
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/main.cpp -o ./bin/rshell
#ls:
#	@mkdir -p bin
#	$(CC) $(FLAGS) src/ls.cpp -o bin/ls
#REMINDER:INSERT ls INTO ALL: 
cp: 
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/cp.cpp -o ./bin/cp
mv: 
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/mv.cpp -o ./bin/mv
rm: 
	mkdir -p ./bin
	$(COMPILE) $(FLAG) ./src/rm.cpp -o ./bin/rm

clean:
	rm -rf ./bin

