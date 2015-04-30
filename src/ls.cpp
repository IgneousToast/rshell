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
		if(i == 0)
		{
			argument = ".";
		}
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

void Contents(string s, vector<string> &v) 
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
		string stuff(contents->d_name);
		v.push_back(stuff);
	}
	if(errno != 0)
	{
		perror("readdir()");
		exit(1);
	}
	if(closedir(direct) == -1)
	{
		perror("closedir()");
		exit(1);
	}

}
int id_dot_pos(vector<string> &D)
{
	int a = 0;
	vector <string> v;
	for(unsigned int i = 0; i < D.size(); i++)
	{
		string s = D.at(i)	;
		Contents(s, v);
		for(unsigned int j = 0; j < v.size(); j++)
		{
			if(v.at(j).at(0) == '.')
			{
				a++;
			}
		}
	}
	if(a == 0)
	{
		return 0;
	}
	else
	{
		return a; 
	}
}

void Display_Dot(vector <string> V, unsigned int x)
{
	string dot = ".";
	Contents(dot, V);
	for(unsigned int i = x; i < V.size(); i++)
	{
		cout << V.at(i) << " ";
	}
	return;
}
int main(int argc, char** argv)
{
	vector<string> Dirs, flags, stuff;
	fill_vector(argc,argv,Dirs, flags);
	if(argc == 1)
	{
		Display_Dot(stuff, id_dot_pos(Dirs));
		cout << endl;
	}
	else
	{
		char a = 'a'; 
		bool found_a = found_char(flags, a);
		if(!found_a)
		{
			for(unsigned int i = 1; i < Dirs.size(); i++)
			{
				string s = Dirs.at(i);
				Contents(s,stuff);	
				for(unsigned int j = 2 ; j < stuff.size(); j++)
				{
					cout << stuff.at(j) << " ";
				}
				cout << endl;
				stuff.clear();
			}
		}
		else if(found_a)
		{
			if(Dirs.size() == 1)
			{
				Display_Dot(stuff, 0);
				cout << endl;
			}
			else
			{
				for(unsigned int i = 1; i < Dirs.size(); i++)
				{
					string s = Dirs.at(i);
					Contents(s, stuff);
					for(unsigned int j = 0 ; j < stuff.size(); j++)
					{
						cout << stuff.at(j) << " ";
					}
					cout << endl;
					stuff.clear();
				}
			}
		}
	}
	return 0;
}
