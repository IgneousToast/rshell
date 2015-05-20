    #include <iostream>
    #include <unistd.h>
    #include <stdio.h>
	#include <stdlib.h>
    #include <signal.h>		//control C

    using namespace std;
	int c, quit, z=0;

	void handler(int x)
	{
		if(x==SIGINT)
		{
		//	exit(1);
			cout << "c";
			c++;
		}
		else if (x== SIGQUIT) 
		{
			cout<<"\\";
			quit++;
		}
		else if(x == SIGTSTP)
		{
			cout << 's';
			z++;
		}

	}
    int main()
    {
		struct sigaction sa;
		sa.sa_handler=handler;
		
		while(true)
		{
			cout<<"x"<<flush;
            sleep(1);
			if(sigaction(SIGQUIT,&sa, NULL)==-1) perror("SIGQUIT"); 
			else if(sigaction(SIGINT,&sa, NULL)==-1) perror("SIGINT");
			else if(sigaction(SIGTSTP,&sa, NULL)==-1) perror("SIGTSTP");
			if(z==3) break;
        }
		cout<<endl;
		cout<<"The number of time ctrl-c: "<<c<<endl;
		cout<<"The number of time ctrl-\\: "<<quit<<endl;
		cout<<"The number of time ctrl-z: "<<z<<endl;
		return 0;
    }
