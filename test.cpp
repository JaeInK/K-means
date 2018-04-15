#include <fstream>	
#include <iostream>	
#include <stdlib.h>	
#include <unistd.h>	
#include <sys/wait.h>	
#include <sys/types.h>	
#include <sys/shm.h>
#include <sys/stat.h>

using namespace std;

int *v;


int main()
{
	for(int i=0; i<3; i++)
	{
   int shmid;
   shmid = shmget(IPC_PRIVATE, 10*sizeof(int), S_IRUSR | S_IWUSR);
   if(shmid == -1)
   {
	   printf("Shmget Error\n");
	   exit(1);			
   }
	v = (int *)shmat(shmid, NULL,0); 
 	//v = new int[5];
   pid_t pid = fork();
   //cout<<i<<" "<<pid<<endl;
   if (pid == -1) {
      exit(EXIT_FAILURE);
   } else if (pid == 0) {
      cout<<"child\n";
	  v[0]=3;
      kill(getpid(), SIGTERM);
	  //cout<<"WHAT?";
   } else {
      int status;
	  v[1]=2;
	  cout<<"parent\n";
      waitpid(pid, &status, 0);
   }

//	shmdt((void *) v);
   cout<<v[0]<<endl;
   cout<<v[1];
	}
   return EXIT_SUCCESS;
}
