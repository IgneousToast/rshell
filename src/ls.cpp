#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>

using namespace std;

void fill_vector(int size, vector<string> &d, vector<string> &f, char** A)
{
	string argument;
	for(int i = 0; i < size ;i++)
	{
		argument = A[i];
		if(argument.at(0) == '-')
		{
			f.push_back(argument);
		}
		else
		{
			d.push_back(argument);
		}
	}
	return;
}

bool found_char(vector<string> &v, char letter)
{
	for(unsigned int i = 0; i < v.size(); i++)
	{
		int found = v.at(i).find(letter);		
		if(found != -1)
		{	
			return true;
		}
	}
	return false;

}

int main(int argc, char** argv)
{
	vector<string> Dirs, flags;
	fill_vector(argc,Dirs, flags,argv);
	
		
	//string files(filespecs ->d_name)
	
	if(argc <= 1)
	{
		// ls stuff
	}
	else
	{
		char a = 'a'; 
		bool found_a = found_char(flags, a);
		cout << found_a << endl;	
		DIR *direct;
		struct dirent *contents;
		errno = 0;

		if((direct = opendir(argv[1]))	== NULL)
		{
			perror("opendir()");
			exit(1);
		}
		while((contents = readdir(direct)) != NULL)
		{
			cout << contents->d_name << " ";
		}
		if(errno != 0)
		{
			perror("readdir()");
			exit(1);
		}
		cout << endl;
		if(closedir(direct) == -1)
		{
			perror("closedir()");
			exit(1);
		}

	}
	return 0;
}
	
	/*for(unsigned int i = 0; i < argu.size(); i++)
	{
		cout << argu.at(i) << endl;
	}*/	
 
