#include <iostream>
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
	for(unsigned int i = 0; i < w.size(); i++)
	{
		if(w.at(i).at(0) == '.')
		{
			loc.push_back(i);
		}
	}
	for(unsigned int i = 0; i < loc.size(); i++)
	{
		w.erase(w.begin());
	}
	sort(w.begin(), w.end(), alphabetical);
}
/*int id_dot_pos(vector<string> &D)
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
		return a;
	}
	else
	{
		return a; 
	}
}
*/
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
				with_dot.clear();
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
int main(int argc, char** argv)
{
	vector<string> Dirs, flags, with_dot, without_dot;
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
		//char l = 'l'; 
		bool found_a = found_char(flags, a);
		//bool found_l = found_char(flags, l);
		dash_a(found_a,Dirs,flags,with_dot,without_dot);
	}
	return 0;
}
