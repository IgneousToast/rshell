#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

using namespace std;

int main()
{
	string username;	
	if(getlogin() == NULL)
	{
		perror( getlogin());
	}
	else
	{
		username =  getlogin();
		cout << username << endl;
	}
	return	0;
}
