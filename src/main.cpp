#include <vector>
#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

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

void comments(string &cmd)
{
	if(cmd.find("#") == string :: npos)
	{
		return;
	}
	else
	{
		cmd.erase(cmd.find("#"), cmd.size());
	}
	return;
}
void find_position(const string command, vector<int> &positions)
{	
	positions.clear();
	for(unsigned int i = 0; i < command.size(); i++)
	{
		if((command.at(i) == '&') && (command.at(i+1) == '&'))
		{
			positions.push_back(i);
		}
		else if((command.at(i) == '|') && (command.at(i+1) == '|'))
		{
			positions.push_back(i);
		}
		else if ((command.at(i) == ';'))
		{
			positions.push_back(i);
		}
	}
}

bool find_connectors(const string command, vector<int>& Connects)
{	
	Connects.clear();
	for(unsigned int i = 0; i < command.size(); i++)
	{
		if((command.at(i) == '&') && (command.at(i+1) == '&'))
		{
			Connects.push_back(0);
		}
		else if((command.at(i) == '|') && (command.at(i+1) == '|'))
		{
			Connects.push_back(1);
		}
		else if ((command.at(i) == ';'))
		{
			Connects.push_back(2);
		}
	}
	if(command.at(0) == '&' || command.at(0) == ';' || command.at(0) == '|')
	{
		return true; 
	}
	return false;
}
/*
char* parse(const string cmd, int position, int )
{
 	char* C_Array = new char [cmd.length()+1];
	strcpy (C_Array, cmd.c_str());
	
	char* token = strtok (C_Array, delim);
	unsigned int i = 0;
	while (token != 0)
	{
		cout << token << " " ;
		token = strtok(NULL,delim);
		i++;
	}
	delete[] C_Array;
	delete[] delim;

	return token;
}
*/
void forking(char** parameter, int& status)
{
	int check_fork = fork();
	if(check_fork == -1)
	{
		perror("Error: fork()");
		exit(1);
	}
	else if(check_fork == 0) 
	{
		if(execvp(parameter[0],parameter) == -1)
		{
			status = -1;
			perror("Error: execvp()");
		}
		exit(1);
	}
	else
	{
		int check_wait = wait(&status);
		if(check_wait == -1)
		{
			perror("Error: wait()");
		}

	}
}

int main()
{
	//Initialize all variables
	string command, delimiter;
	vector<int> my_connector;
	vector<char*> parsed_cmd;
//	char *args[MEMORY];
	vector<int> positions;
	vector<int> connectors; 
	bool Exit = false;
	string Exit_command = "exit";

	while(!Exit)
	{
		bool connector_first = false;
		display_user(); // Displays username and $
		getline(cin, command); // gets the command
		comments(command); // checks for comments
		connector_first = find_connectors(command, connectors); // find the connectors in the command, returns a bool that tells if there is a in the first position 
		if(connector_first) // checks if connector is before any arguments
		{
			Exit = true;
			cout << "Error: Need argument before connector!"; //if true, couts error, exits 
		}
		find_position(command, positions); // finds the positions of the connectors and puts them in a vector of ints
		
	}
	
}
