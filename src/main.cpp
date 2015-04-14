<<<<<<< HEAD
#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

>>>>>>> d76b6fd7c712dbd8a20a21f664434d277a4c00b8
