#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
	string username;
	if(getlogin() == NULL)
	{
		perror("getline()");
	}
	else
	{
		username = getlogin();
		cout << endl;
	}



	return 0;
}

