#include <vector>
#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
using namespace std;


#define MEMORY 200000 // size of memory allocation for commands

void display_user() //displays the login name followed by a '@' followed by the hostname
{
	string login, user;
        char host[64];
        if(getlogin() == NULL) //IF LOGIN is NULL outputs an error message
        {
                perror("getline()");
        }
        else // else login is assigned the user login name
        {
                login = getlogin();
        }
        if(gethostname(host, sizeof host) == -1) //if gethostname returns a -1, it outputs an error message
        {
                perror("gethostname()");
        }
        else
        {
                gethostname(host, sizeof host); // else it takes in a char array "host" as a parameter and fills it in with the host name.
        }
        user = login + "@" + host + "$ "; //user is the concantinated string of login and hostname, seperated by and "@"
	cout << user;
}
vector<int> find_connectors(const string command)
{	
	vector<int> Connectors;
	for(unsigned int i = 0; i < command.size(); i++)
	{
		if((command.at(i) == '&') && (command.at(i+1) == '&'))
		{
			Connectors.push_back(0);
		}
		else if((command.at(i) == '|') && (command.at(i+1) == '|'))
		{
			Connectors.push_back(1);
		}
		else if ((command.at(i) == ';'))
		{
			Connectors.push_back(2);
		}
	}
	return Connectors;
}

vector<char*> parse(const string cmd, const string delimiter)
{
	vector <char*> Tokens;
	char* delim = new char [delimiter.length()+1];
 	char* C_Array = new char [cmd.length()+1];
	strcpy(delim, delimiter.c_str());
	strcpy (C_Array, cmd.c_str());
	
	char* token = strtok (C_Array, delim);
	while (token != 0)
	{
		Tokens.push_back(token);
		token = strtok(NULL,delim);
	}
	delete[] C_Array;
	delete[] delim;
	return Tokens;
}

int main()
{
	string command, delimiter;
	vector<int> my_connector;
	display_user();
	getline(cin, command);
	my_connector = find_connectors(command);
	for(unsigned int i = 0; i < my_connector.size(); i++)
	{
		cout << my_connector.at(i) << endl;
	}	
	delimiter = "|&; ";
	//first_parse = parse(command, delimiter);	
	//execvp(manipulated command as a char*,arg[] with all the commands in the char array
	
}
