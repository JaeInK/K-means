#include <fstream>	
#include <iostream>	
#include <stdlib.h>	
#include <unistd.h>	
#include <sys/wait.h>	
#include <sys/types.h>	

using namespace std;

int main()
{
   for(int i=0; i<5; i++)
   {
   pid_t pid = fork();
   //cout<<i<<" "<<pid<<endl;
   if (pid == -1) {
      exit(EXIT_FAILURE);
   } else if (pid == 0) {
      cout<<"child\n";
      kill(getpid(), SIGTERM);
	  //cout<<"WHAT?";
   } else {
      int status;
	  cout<<"parent\n";
      waitpid(pid, &status, 0);
   }
   }
   return EXIT_SUCCESS;
}
