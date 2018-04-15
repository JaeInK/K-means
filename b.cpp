#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/shm.h>


using namespace std;

double **V;
double *clus;
vector< vector<double> > center;
void* fcalDistance(void *);
void* bcalDistance(void *);
int pointnum;

int main()
{
	//read input		
	int testnum;
	int repeatnum;
	int clusternum;
	string str1;
	string str2;

	cout<<"start";
	cin >> testnum;
	cout << testnum;
	cout << "\n";
	for(int t=0; t<testnum; t++)
	{
		int start_s=clock();
		cout<<"repeat";
		cin >> repeatnum;
		cout<<repeatnum;
		cin >> clusternum;
		cout<<clusternum;
		cin >> pointnum;
		cout<<pointnum<<' ';
		V = new double*[pointnum];
		//share data clus
		int shmid;
		shmid = shmget(IPC_PRIVATE, pointnum*sizeof(double), S_IRUSR | S_IWUSR);
		if(shmid ==-1)
		{
			cout<<"Shmget ERROR \n";
			exit(1);
		}
		clus = (double *)shmat(shmid, NULL, 0);
		for(int i=0; i<pointnum; i++)
		{
			V[i]= new double[3];
		}

		for(int j=0; j<pointnum; j++)
		{
			cin>>str1;
			cin>>str2;
			V[j][0] = atof(str1.c_str());
			V[j][1] = atof(str2.c_str());
			V[j][2] = 0;
			//clus[j] = 0;
			//V[i][2] represents which cluster a point is involved in
		}

		//K-Means-Clustering
		for(int k=0; k<repeatnum; k++)
		{
			if(k==0)
			{
				for(int j=0; j<clusternum; j++)
				{
					vector< double > tmp;
					tmp.push_back(V[j][0]);
					tmp.push_back(V[j][1]);
					center.push_back(tmp);
					tmp.clear();
				}
			}
		
			//Setting Cluster for each points / Multiprocess
			pid_t pid =fork();
			if(pid<0)
			{
				//failed to fork
				exit(EXIT_FAILURE);
			}
			
			else if(pid==0)
			{
				//child process
				fcalDistance(NULL);
				kill(getpid(), SIGTERM);
			}
			
			else
			{
				//parent process
				bcalDistance(NULL);
				int status;
				waitpid(pid, &status, 0);
			}
			//Rearranging Clusters' centers
			for(int i=0; i<clusternum; i++)
			{
				double sumx = 0;
				double sumy = 0;
				int num = 0;
				for(int j=0; j<pointnum; j++)
				{
					if(V[j][2] == i)
					{
						sumx = sumx + V[j][0];
						sumy = sumy + V[j][1];
						num = num+1;
					}
				}
				center[i][0] = sumx/num;
				center[i][1] = sumy/num;
			}
		}

		//Printing output
		int stop_s=clock();
		cout<<"Test Case #"<<t<<endl;
		cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000000 << " microseconds"<<endl;
		for(int k=0; k<pointnum; k++)
		{
			cout<<clus[k]<<endl;
		}
		cout<<endl;

		delete[] V;
		center.clear();
	}
}


void* fcalDistance(void *unused)
{
	cout<<"c\n";
	for(int i=0; i<pointnum/2; i++)
	{
		double apoint[2] = {V[i][0], V[i][1]};
		double min = pow(apoint[0]-center[0][0], 2) + pow(apoint[1]-center[0][1], 2);
		//V[i][2]=0;
		clus[i]=0;
		for(int j=1; j<center.size(); j++)
		{
			double distance = pow(apoint[0]-center[j][0], 2) + pow(apoint[1]-center[j][1], 2);
			if(distance < min)
			{
				min = distance;
				V[i][2] = j;
				clus[i] = j;
			}
		}	
	}
	return NULL;
}

void* bcalDistance(void *unused)
{ 
	cout<<"p\n";
	for(int i=pointnum/2; i<pointnum; i++)
	{
		double apoint[2] = {V[i][0], V[i][1]};
		double min = pow(apoint[0]-center[0][0], 2) + pow(apoint[1]-center[0][1], 2);
		clus[i]=0;
		for(int j=1; j<center.size(); j++)
		{
			double distance = pow(apoint[0]-center[j][0], 2) + pow(apoint[1]-center[j][1], 2);
			if(distance < min)
			{
				min = distance;
				V[i][2] = j;
				clus[i] = j;
			}
		}	
	}
	return NULL;
}



