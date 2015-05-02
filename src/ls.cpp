#include <iostream>
#include <iomanip>
#include <grp.h>
#include <pwd.h>
#include <cstdlib>
#include <algorithm>
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
#include "ls_al.h"
using namespace std;


void find_directories(vector <string> &w, vector<string> &j, string &path)
{
	for(unsigned int i = 0; i < w.size(); i++)
	{
		struct stat buffer;	
		if(lstat(path.c_str(), &buffer) == -1)
		{
			perror("lstat()");
			exit(1);
		}
		if(S_ISDIR(buffer.st_mode))
		{
			if(w.at(i).at(0) == '.')
			{
				if(w.at(i) != "..")
				{	
				//	cout << "i = " << i << ": " << w.at(i) << endl;
					j.push_back(w.at(i));
				}
			}
			else
			{
			//	cout << "i = " << i << ": " << w.at(i) << endl;
				j.push_back(w.at(i));
			} 
		}
	}
}

int main(int argc, char** argv)
{
	vector<string> Dirs, flags, with_dot, without_dot, just_directories;
	fill_vector(argc,argv,Dirs, flags);
	string s = Dirs.at(0);
	Contents(s, with_dot, without_dot);
	if(argc == 1)
	{
		Display(without_dot);
		cout << endl;
	}
	else
	{
		char a = 'a';
		char l = 'l'; 
		char R = 'R';
		bool found_a = found_char(flags, a);
		bool found_l = found_char(flags, l);
		bool found_R = found_char(flags, R);
		if((!found_a) && (!found_l) && (!found_R))
		{

			dash_a(found_a,Dirs,flags,with_dot,without_dot);

		}
		else if((found_a) && (!found_l) && (!found_R))
		{
			dash_a(found_a,Dirs,flags,with_dot,without_dot);
		}
		if((found_l) && (!found_R))
		{
			if(Dirs.size() == 1)
			{
				if(found_a)//ls -la or any variation
				{
					for(unsigned int i = 0; i < with_dot.size(); i++)
					{
						const char* b = with_dot.at(i).c_str();
						string p;
						struct stat file;
						stat(b, &file);
						dash_l(p, file, b);
					}

				}
				else if (!found_a)
				{
 					for(unsigned int i = 0; i < without_dot.size(); i++)
					{
						const char* b = without_dot.at(i).c_str();
						string p;
						struct stat file;
						stat(b, &file);
						dash_l(p, file, b);
					}
				}
			}
			else
			{
				if(found_a)	// ls-la for multiple files
				{
					for(unsigned int j = 1; j < Dirs.size(); j++)
					{
						s = Dirs.at(j);
						with_dot.clear();
						cout << s << ": " << endl;
						Contents(s,with_dot, without_dot);
						for(unsigned int i = 0; i < with_dot.size(); i++)
						{
							const char* b = with_dot.at(i).c_str();
							string p;
							struct stat file;
							stat(b, &file);
							dash_l(p, file, b);
						}
						with_dot.clear();
					}
				}
				else if(!found_a)
				{	
					for(unsigned int j = 1; j < Dirs.size(); j++)
					{
						s = Dirs.at(j);
						cout << s << ": " << endl;
						with_dot.clear();
						Contents(s,with_dot, without_dot);
						for(unsigned int i = 2; i < with_dot.size(); i++)
						{
							const char* b = with_dot.at(i).c_str();
							string p;
							struct stat file;
							stat(b, &file);
							dash_l(p, file, b);
						}
						with_dot.clear();
					}

				}
			}
		}
		else if(found_R)
		{
			if(Dirs.size() == 1) // bin/ls -R
			{
				if((!found_a) && (!found_l))// ls -R
				{
				}
				else if((found_a) && (!found_l)) // ls -Ra
				{
	
				}
				else if((!found_a) && (found_l))//ls -Rl
				{
	
				}
				else if((found_a) && (found_l)) //ls -Rla
				{

				}
			}
			else //multiple folders
			{
				if((!found_a) && (!found_l))// ls -R tests
				{
		
				}
				else if((found_a) && (!found_l)) // ls -Ra tests 
				{
	
				}
				else if((!found_a) && (found_l))//ls -Rl tests
				{
	
				}
				else if((found_a) && (found_l)) //ls -Rla tests
				{

				}
			}
		}
	}
	return 0;
}
