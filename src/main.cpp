#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
}


int main()
{
	display_user();
	return 0;
}

