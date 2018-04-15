#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <ctime>

using namespace std;

double **V;
double *clus;
double **center;
void* calDistance(void *);
int clusternum;
int pointnum;

int main()
{
	//read input		
	int testnum;
	int repeatnum;
	string str1;
	string str2;

	cin >> testnum;
	for(int t=0; t<testnum; t++)
	{
		//initialize
		int start_s=clock();
		cin >> repeatnum;
		cin >> clusternum;
		cin >> pointnum;
		V = new double*[pointnum];//V has all points 
		center = new double*[pointnum];//center has all clusters' center
		clus = new double[pointnum];
		for(int i=0; i<pointnum; i++)
		{
			V[i] = new double[2];
			center[i] = new double[2];
		}
		
		for(int j=0; j<pointnum; j++)
		{
			cin>>str1;
			cin>>str2;
			V[j][0] = atof(str1.c_str());
			V[j][1] = atof(str2.c_str());
			clus[j]=0;
			//clus represents which cluster a point is involved in
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
		
			//Setting Cluster for each points
			calDistance(NULL);

			//Rearranging Clusters' centers
			for(int i=0; i<clusternum; i++)
			{
				double sumx = 0;
				double sumy = 0;
				int num = 0;
				for(int j=0; j<pointnum; j++)
				{
					if(clus[j] == i)
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
		//cout<< "repeat: "<<repeatnum<<endl;
		//cout<< "cluster: "<<clusternum<<endl;
		//cout<< "pointnum: "<<pointnum<<endl;
		cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000000 << " microseconds"<<endl;
		for(int k=0; k<pointnum; k++)
		{
			cout<<clus[k]<<endl;
		}
		
		delete[] V;
	}
}


void* calDistance(void *unused)//calculate distances from all clusters' center
{
	for(int i=0; i<pointnum; i++)
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
				clus[i]=j;
			}
		}	
	}
	return NULL;
}
