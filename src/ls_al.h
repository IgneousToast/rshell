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

using namespace std;


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
bool alphabetical(string start, string next)
{
	transform(start.begin(), start.end(), start.begin(), ::tolower);
	transform(next.begin(), next.end(), next.begin(), ::tolower);
	if(start.at(0) == '.')
	{
		return lexicographical_compare(start.begin() + 1, start.end(), next.begin(), next.end());
	}
	else if(next.at(0) == '.')
	{	
		return lexicographical_compare(start.begin(), start.end(), next.begin() + 1, next.end());
	}
	else if((start.at(0) == '.') && (next.at(0) == '.'))
	{
		return lexicographical_compare(start.begin() + 1, start.end(), next.begin() + 1, next.end());
	}
	else
	{
		return lexicographical_compare(start.begin(), start.end(), next.begin(), next.end());
	}
}
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
	sort(d.begin(), d.end(), alphabetical);
	return;
}

void Group_p(string &permissions, struct stat file)
{
	(file.st_mode & S_IRGRP) ? permissions += "r" : permissions += "-";
	(file.st_mode & S_IWGRP) ? permissions += "w" : permissions += "-";	
	(file.st_mode & S_IXGRP) ? permissions += "x" : permissions += "-";
}

void User_p(string &permissions, struct stat file) 
{
	if (file.st_mode & S_IFREG) permissions += "-";
	else if (file.st_mode & S_IFDIR) permissions += "d"; 
	else if (file.st_mode & S_IFCHR) permissions += "c"; 
	else if (file.st_mode & S_IFBLK) permissions += "b"; 
	(file.st_mode & S_IRUSR) ? permissions += "r" : permissions += "-";
	(file.st_mode & S_IWUSR) ? permissions += "w" : permissions += "-";
	(file.st_mode & S_IXUSR) ? permissions += "x" : permissions += "-";
}

void Other_p(string &permissions, struct stat file)
{
	(file.st_mode & S_IROTH) ? permissions+= "r" : permissions += "-";
	(file.st_mode & S_IWOTH) ? permissions+= "w" : permissions += "-";
	(file.st_mode & S_IXOTH) ? permissions+= "x" : permissions += "-";
	cout << permissions << " ";
}
void Display(vector <string> &V)
{
	for(unsigned int i = 0; i < V.size(); i++)
	{
		cout << V.at(i) << " ";
	}
	return;
}
void Display_Mult(vector <string> &V, string s)
{
	cout << s << ":" << endl;
	for(unsigned int i = 0; i < V.size(); i++)
	{
		cout << V.at(i) << " ";
	}
	return;
}
void Contents(string s, vector<string> &v, vector<string> &w) 
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
		w.push_back(stuff);
		sort(v.begin(), v.end(), alphabetical);
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
	vector<int> loc;
	unsigned int a = w.size();
	for(unsigned int i = 0; i < a; i++)
	{
		if(w.at(0).at(0) == '.')
		{
			w.erase(w.begin());
		}
		a = w.size();
	}
	sort(w.begin(), w.end(), alphabetical);
}

void dash_a(bool found_a, vector <string> &Dirs, vector<string> &flags, vector <string> with_dot, vector<string> without_dot)
{
	with_dot.clear();
	without_dot.clear();
	if(!found_a)
	{
		if(Dirs.size() == 2)
		{
			for(unsigned int i = 1; i < Dirs.size(); i++)
			{ 
				string s = Dirs.at(i);
				Contents(s, with_dot, without_dot);
				Display(without_dot);
				cout << endl;
				without_dot.clear();
			}
		}
		else
		{

			for(unsigned int i = 1; i < Dirs.size(); i++)
			{
				string s = Dirs.at(i);
				Contents(s, with_dot, without_dot);
				Display_Mult(without_dot,s);
				cout << endl << endl;
				without_dot.clear();
			}
		}
	}
	else if(found_a)
	{
		if(Dirs.size() == 1)
		{
			string s = Dirs.at(0);
			Contents(s,with_dot,without_dot);
			Display(with_dot);
			cout << endl;
		}
		else
		{
			if(Dirs.size() == 2)
			{
				for(unsigned int i = 1; i < Dirs.size(); i++)
				{ 
					string s = Dirs.at(i);
					Contents(s, with_dot, without_dot);
					Display(with_dot);
					cout << endl;
					with_dot.clear();
	
				}
			}
			else
			{
				for(unsigned int i = 1; i < Dirs.size(); i++)
				{ 
					string s = Dirs.at(i);
					Contents(s, with_dot, without_dot);
					Display_Mult(with_dot, s);
					cout << endl << endl;
					with_dot.clear();
				}
			}
		}
	}
}

void dash_l(string &perms, struct stat file, const char* a)
{
	User_p(perms, file);
	Group_p(perms, file);
	Other_p(perms, file);

	struct passwd *usr;
	struct group *grp;
	if((usr = getpwuid(file.st_uid)) == NULL)
	{
		perror("getpwuid()");
		exit(1);
	}
	if((grp = getgrgid(file.st_gid)) == NULL)
	{
		perror("getgrgid()");
		exit(1);
	}
	
	struct tm TIME;
	localtime_r(&file.st_mtime, &TIME);
	char t_array[80];
	strftime((char*)& t_array, 80, " %b %d %H:%M", &TIME); 

	cout << setw(1)<< file.st_nlink;
	cout << setw(1) << " "  << usr -> pw_name 
		<< setw(1) << " " << grp -> gr_name << " "; 
	cout.width(5);
	cout << right  << file.st_size;
	cout.width(5);
	cout << setw(1) << " "  << t_array;
	cout.width(5);
	cout << setw(1) << left <<  " "  << a << endl;
	perms = "";
}
