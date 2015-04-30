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

void fill_vector(int size, char** A, vector<string> &d, vector<string> &f)
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


void ls_a(string s) 
{
	DIR *direct;
	struct dirent *contents;
	errno = 0;
	const char *c = s.c_str();
	if((direct = opendir(c)) == NULL)
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
int main(int argc, char** argv)
{
	vector<string> Dirs, flags;
	fill_vector(argc,argv,Dirs, flags);
			
	
		
	//string files(filespecs ->d_name)
	if(argc == 1)
	{
		string dot = ".";
		ls_a(dot);
	}
	else
	{
		char a = 'a'; 
		bool found_a = found_char(flags, a);
		vector<string> Dirs, flags;
		fill_vector(argc,argv,Dirs, flags);
	
		if(found_a)
		{
			if(Dirs.size() == 1)
			{
				string dot = ".";
				ls_a(dot);	
			}
			else
			{
				for(unsigned int i = 1; i < Dirs.size(); i++)
				{
					string s = Dirs.at(i);
					ls_a(s);
				}
			}
		}

	}
	return 0;
}
	
	/*for(unsigned int i = 0; i < argu.size(); i++)
	{
		cout << argu.at(i) << endl;
	}*/	
 
