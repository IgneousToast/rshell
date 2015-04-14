#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
using namespace std;


void display_user()
{
	string login;
        char host[64];
        string user;
        if(getlogin() == NULL)
        {
                perror("getline()");
        }
        else
        {
                login = getlogin();
        }
        if(gethostname(host, sizeof host) == -1)
        {
                perror("gethostname()");
        }
        else
        {
                gethostname(host, sizeof host);
        }
        user = login + "@" + host;
        cout << user << endl;


}


int main()
{
	display_user();
	return 0;
}

