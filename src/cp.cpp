#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Timer.h"

using namespace std;

void cpy_1(const char* srce, const char* dest)
{
	//get and put
	//cpy input file to output file one character at a time
	char hold;
	ifstream source(srce);
	ofstream destination(dest);
	int fdnew;
	int fdold;
	if(-1 == (fdnew = open(dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
	{
		perror("open() error");
		exit(1);
	}
	if(-1 == (fdold = open(srce, O_RDONLY)))
	{
		perror("open() error");
		exit(1);
	}
	while(source.get(hold) != NULL)
	{
		destination.put(hold);
	}
	source.close();
}
void cpy_2(const char* srce, const char* dest)
{
	//read and write
	//cpy input file to output file one one char at a time
	int fdnew;
	int fdold;
	if(-1 == (fdnew = open(dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
	{
		perror("open() error");
		exit(1);
	}
	if(-1 == (fdold = open(srce, O_RDONLY)))
	{
		perror("open() error");
		exit(1);
	}
	int size;
	char c[1]; // = NULL;
	if(-1 == (size = read(fdold, c, 1)))
	{
		perror("read() error");
		exit(1);
	}
	while(size > 0)
	{
		if(-1 == write(fdnew, c, size))
		{
			perror("write() error");
			exit(1);
		}
		if(-1 == (size = read(fdold, c, 1)))
		{
			perror("read() error");
			exit(1);
		}
	}
	if(-1 == close(fdnew))
	{
		perror("close() error");
		exit(1);
	}
	if(-1 == close(fdold))
	{
		perror("close() error");
		exit(1);
	}
}
void cpy_3(const char* srce, const char* dest)
{
	//read and write
	//cpy input file to output file one buffer at a time
	//buffer is of size BUFSIZ
	int fdnew;
	int fdold;
	if(-1 == (fdnew = open(dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
	{
		perror("open() error");
		exit(1);
	}
	if(-1 == (fdold = open(srce, O_RDONLY)))
	{
		perror("open() error");
		exit(1);
	}
	int size;
	char c[BUFSIZ];
	if(-1 == (size = read(fdold, c, sizeof(c))))
	{
		perror("read() error");
		exit(1);
	}
	while(size > 0)
	{
		if(-1 == write(fdnew, c, size))
		{
			perror("write() error");
			exit(1);
		}
		if(-1 == (size = read(fdold, c, sizeof(c))))
		{
			perror("read() error");
			exit(1);
		}
	}
	if(-1 == close(fdnew))
	{
		perror("close() error");
		exit(1);
	}
	if(-1 == close(fdold))
	{
		perror("close() error");
		exit(1);
	}
}
int main(int argc, const char* argv[])
{
	
	if(argc > 4 || argc < 3)
	{
		perror("Invalid: amount of elements");
		exit(1);
	}

	const char* srce = argv[1];
	const char* dest = argv[2];
	Timer time;
	double t_sec = 0;

	if(argc == 3)
	{
		cpy_3(srce, dest);
	}
	else if(argc == 4)
	{
		if(!strcmp(argv[3], "-a"))
		{
			struct stat buf;
			if(stat(dest, &buf) != -1)
			{
				perror("destination exists");
				exit(1);
			}

			cout << "cpy_1: " << endl;
			cout << flush;
			time.start();
			cpy_1(srce, dest);
			time.elapsedWallclockTime(t_sec);
			cout << "Wall Clock: " << t_sec << " seconds" << endl << flush;
			time.start();
			cpy_1(srce, dest);
			time.elapsedUserTime(t_sec);
			cout << "User Time: " << t_sec << " seconds" << endl << flush;
			time.start();
			cpy_1(srce, dest);
			time.elapsedSystemTime(t_sec);
			cout << "System Time: " << t_sec << " seconds" << endl << flush;
			cout << endl << flush;

			cout << "cpy_2: " << endl;
			cout << flush;
			time.start();
			cpy_2(srce, dest);
			time.elapsedWallclockTime(t_sec);
			cout << "Wall Clock: " << t_sec << " seconds" << endl << flush;
			time.start();
			cpy_2(srce, dest);
			time.elapsedUserTime(t_sec);
			cout << "User Time: " << t_sec << " seconds" << endl << flush;
			time.start();
			cpy_2(srce, dest);
			time.elapsedSystemTime(t_sec);
			cout << "System Time: " << t_sec << " seconds" << endl << flush;
			cout << endl << flush;
		
			cout << "cpy_3: " << endl;
			cout << flush;
			time.start();
			cpy_3(srce, dest);
			time.elapsedWallclockTime(t_sec);
			cout << "Wall Clock: " << t_sec << " seconds" << endl << flush;
			time.start();
			cpy_3(srce, dest);
			time.elapsedUserTime(t_sec);
			cout << "User Time: " << t_sec << " seconds" << endl << flush;
			time.start();
			cpy_3(srce, dest);
			time.elapsedSystemTime(t_sec);
			cout << "System Time: " << t_sec << " seconds" << endl << flush;
			cout << endl << flush;
		}
		else
		{
			perror("Invalid: argv[3]");
			exit(1);
		}
	}
	else
	{
		cout << "Something went wrong" << endl;//REMOVE
		exit(1);
	}
	return 0;
}
