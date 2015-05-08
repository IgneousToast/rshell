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
		cmd += " ";
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
	positions.push_back(command.size());
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
	Connects.push_back(command.size());
	if(command.at(0) == '&' || command.at(0) == ';' || command.at(0) == '|')
	{
		return true; 
	}
	return false;
}

int main()
{
	//Initialize all variables
	string command, delimiter;
	vector<int> my_connector;
	char* arguments[200000] = {0}; //Rshell is only able to take in 200000 arguments
	vector<int> positions; // positions of connectors in command
	vector<int> connectors;// connector ids in command
	bool Exit = false; //bool exit variable
	string Exit_command = "exit"; // string exit command 

	while(!Exit)
	{
		int status;
		unsigned int x = 0;//keeps track of amount of arguments
		display_user(); // Displays username and $
		getline(cin, command); // gets the command
		
		if(command == "exit") //if the first command is exit, then exit program
		{
			exit(0);
		}
		while(command.substr(x,1) !="")
		{
			comments(command); // checks for comments and erases them from the string command

			find_position(command, positions); // finds the positions of the connectors and puts them in a vector of ints
			find_connectors(command, connectors);
			char* Command_Array = new char [command.length()+1]; 
			strcpy (Command_Array, command.c_str());// these two lines create a c_string of the command inputted
											
			char* token = strtok (Command_Array, "|&; \t"); // parses the commands with the delimiters
			while (token != NULL) // filling array with parsed command/tokens 
			{
				arguments[x] = token; // inputs each indiviual argument into the arguments array
				token = strtok(NULL, "|;\t"); // parses until entire command is done
				x++; // keeps the counts of the number of arguments inputted
			}
			
			int check_fork = fork(); //calls the forking function, creates a child process
			if(check_fork == -1)
			{
				perror("Error: fork()"); // fork error message
				exit(1); // exits 1 if error occurs
			}
			else if(check_fork == 0)  // in child process
			{
				if(execvp(arguments[0],arguments) == -1) // uses execvp to call first argument
				{
					perror("Error: execvp()");
					exit(-1);
				}
				exit(0);
			}
			if(wait(&status) == -1) // if wait fails
			{
				perror("Error: wait()"); // outputs wait message, else waits for child process to finish
			}
			unsigned int a = positions.at(x);
			unsigned int k = connectors.at(x);
			
			if(k == 0 && status == 0 && (command.find("&&", a)!= string::npos|| command.find(";", a) != string::npos))
			{
				a = positions.at(k + 1);
				k = k + 2;
			}
			else if(k == 1 && status != 0 && (command.find("||", a)!= string::npos|| command.find(";", a) != string::npos))
			{
				a = positions.at(k + 1);
				k = k + 2;
			}
			else if((k == 2)||(k == 0 && status != 0)||(k == 1 && status == 0))
			{
				a++;
			}
			else
			{
				break;
			}
			x = 0;
			for(unsigned int i = 0; i < x; i++)
			{
				arguments[i] = NULL;
			}
		}
	}

}
