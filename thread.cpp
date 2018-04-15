#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <pthread.h>

using namespace std;

double **V;
double *clus;
double **center;
void* fcalDistance(void *);
void* bcalDistance(void *);
int pointnum;
int clusternum;

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
		center = new double*[pointnum];
		clus = new double[pointnum];
		for(int i=0; i<pointnum; i++)
		{
			V[i]= new double[3];
			center[i] = new double[2];
		}

		for(int j=0; j<pointnum; j++)
		{
			cin>>str1;
			cin>>str2;
			V[j][0] = atof(str1.c_str());
			V[j][1] = atof(str2.c_str());
			V[j][2] = 0;
			clus[j] = 0;
			//V[i][2] represents which cluster a point is involved in
		}

		//K-Means-Clustering
		for(int k=0; k<repeatnum; k++)
		{
			if(k==0)
			{
				for(int j=0; j<clusternum; j++)
				{
					center[j][0] = V[j][0];
					center[j][1] = V[j][1];
				}
			}
		
			//Setting Cluster for each points / Multithread
			pthread_t thread[2];
			int thr_id;
			int status;
			thr_id = pthread_create(&thread[0], NULL, fcalDistance, NULL);
    		if (thr_id < 0)
    		{
        		perror("thread create error : ");
        		exit(0);
    		}	
			thr_id = pthread_create(&thread[1], NULL, bcalDistance, NULL);
			if (thr_id < 0)
			{
				perror("thread create error : ");
				exit(0);
			}
			pthread_join(thread[0], (void **)&status);
			pthread_join(thread[1], (void **)&status);

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
		delete[] center;
	}
}


void* fcalDistance(void *unused)
{
	cout<<"c";
	for(int i=0; i<pointnum/2; i++)
	{
		double apoint[2] = {V[i][0], V[i][1]};
		double min = pow(apoint[0]-center[0][0], 2) + pow(apoint[1]-center[0][1], 2);
		//V[i][2]=0;
		clus[i]=0;
		for(int j=1; j<clusternum; j++)
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
	cout<<"p";
	for(int i=pointnum/2; i<pointnum; i++)
	{
		double apoint[2] = {V[i][0], V[i][1]};
		double min = pow(apoint[0]-center[0][0], 2) + pow(apoint[1]-center[0][1], 2);
		clus[i]=0;
		for(int j=1; j<clusternum; j++)
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



