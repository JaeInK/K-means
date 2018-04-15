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
double *v;
vector< vector<double> > center;
void* fcalDistance(void *);
void* bcalDistance(void *);
int pointnum;
double (*V)[100000];


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

		//share data
		const int size = pointnum*3;
		int segment_id = shmget(IPC_PRIVATE, size*sizeof(double)*1000000, S_IRUSR | S_IWUSR);
		if(segment_id ==-1)
		{
			perror("shmget");
			exit(1);
		}
		//v = (double *)shmat(segment_id, NULL, 0);
		//V = (double **)malloc(pointnum*3*sizeof(double));
		//int handle = shm_open("/shm", O_CREAT | O_RDWR, 0777);
		//ftruncate(handle, pointnum*3);
		//V = (double **)mmap(NULL, pointnum*3, PROT_READ|PROT_WRITE, MAP_SHARED, handle, 0); 

		//shm_fd = shm_open(name, 
		//V = (char **)mmap(0, pointnum*3, PROT_WRITE, MAP_SHARED, shm_fd, 0);
//		V  =(double (*)[100000]) shmat(segment_id,0,0);	
		//V = new double*[pointnum];
//		for(int i=0; i<pointnum; i++)
//		{
	//		//V[i]= new double[3];
	//		V[i] = (double *)shmat(segment_id, NULL, 0);
//		}
		
		for(int j=0; j<pointnum; j++)
		{
			cin>>str1;
			cin>>str2;
			//cout<<save<<endl;
			//double *nums = new double[3];
			double a = atof(str1.c_str());
			double b = atof(str2.c_str());
			double c = 0;
			//nums[0] = a;
			//nums[1] = b;
			//nums[2] = c;
			//save = nums;
			//cout<<save[0]<<save[1]<<save[2];
		//	V[j][0] = a;
		//	V[j][1] = b;
		//	V[j][2] = c;
	 	//	save[0] = a;
		  //  save[1] = b;
			//save[2] = c;
			//V[j][0] = atof(str1.c_str());
			//V[j][1] = atof(str2.c_str());
			//V[j][2] = 0;
			//V[j] = [atof(str1.c_str()), atof(str2.c_str()), 0];
			//V[i][2] represents which cluster a point is involved in
		}
	//	V = &save;
		//cout<<V[0][0]<<endl;
		//cout<<V[1][0]<<endl;

		//K-Means-Clustering
//		for(int k=0; k<repeatnum; k++)
//		{
//			if(k==0)
//			{
//				for(int j=0; j<clusternum; j++)
//				{
//					vector< double > tmp;
//					tmp.push_back(V[j][0]);
//					tmp.push_back(V[j][1]);
//					center.push_back(tmp);
//					tmp.clear();
//				}
//			}
		
			//Setting Cluster for each points / Multiprocess
	//		pid_t pid = fork();
	//		if(pid<0)
	//		{
	//			//failed to fork
	//			exit(EXIT_FAILURE);
	//		}
//
//			else if(pid==0)
//			{
//				//child process
//				fcalDistance(NULL);
//				kill(getpid(), SIGTERM);
//			}
//			
//			else
//			{
//				//parent process
//				bcalDistance(NULL);
//				int status;
//				waitpid(pid,&status,0);
//				shmdt(V);
		//		munmap(V, pointnum*3);
//			}

			//Rearranging Clusters' centers
		//	for(int i=0; i<clusternum; i++)
		//	{
		//		double sumx = 0;
		//		double sumy = 0;
		//		int num = 0;
		//		for(int j=0; j<pointnum; j++)
		//		{
		//			if(V[j][2] == i)
		//			{
		//				sumx = sumx + V[j][0];
		///				sumy = sumy + V[j][1];
		//				num = num+1;
		//			}
		//		}
		//		center[i][0] = sumx/num;
		//		center[i][1] = sumy/num;
		//	}
		//}

		//Printing output
//		int stop_s=clock();
//		cout<<"Test Case #"<<t<<endl;
//		cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000000 << " microseconds"<<endl;
		for(int k=0; k<pointnum; k++)
		{
		//	cout<<V[k][2]<<endl;
		}
		cout<<endl;

		delete[] V;
		center.clear();
	}
}


void* fcalDistance(void *unused)
{
//	for(int i=0; i<pointnum/2; i++)
//	{
//		double apoint[2] = {V[i][0], V[i][1]};
//		double min = pow(apoint[0]-center[0][0], 2) + pow(apoint[1]-center[0][1], 2);
//		V[i][2]=0;
//		for(int j=1; j<center.size(); j++)
//		{
//			double distance = pow(apoint[0]-center[j][0], 2) + pow(apoint[1]-center[j][1], 2);
//			if(distance < min)
///			{
//				min = distance;
//				V[i][2] = j;
//				//cout<<j<<endl;
//			}
//		}	
//	}
//	return NULL;
}

void* bcalDistance(void *unused)
{ 
//	for(int i=pointnum/2; i<pointnum; i++)
///	{
//		double apoint[2] = {V[i][0], V[i][1]};
//		double min = pow(apoint[0]-center[0][0], 2) + pow(apoint[1]-center[0][1], 2);
//		V[i][2]=0;
//		for(int j=1; j<center.size(); j++)
//		{
//			double distance = pow(apoint[0]-center[j][0], 2) + pow(apoint[1]-center[j][1], 2);
//			if(distance < min)
//			{
///				min = distance;
//				V[i][2] = j;
//			}
//		}	
//	}
//	return NULL;
}



