#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <ctime>

using namespace std;

int main()
{
	//read input		
	int testnum;
	int repeatnum;
	int clusternum;
	int pointnum;
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
		vector< vector<double> > V;
		vector<double> tmp;
		for(int j=0; j<pointnum; j++)
		{
			cin>>str1;
			cin>>str2;
			tmp.push_back(atof(str1.c_str()));
			tmp.push_back(atof(str2.c_str()));
			V.push_back(tmp);
			tmp.clear();
		}

		//K-Means-Clustering
		vector< vector<double> > center;
		int clus[pointnum];
		for(int k=0; k<repeatnum; k++)
		{
			if(k==0)
			{
				for(int j=0; j<clusternum; j++)
				{
					tmp.push_back(V[j][0]);
					tmp.push_back(V[j][1]);
					center.push_back(tmp);
					tmp.clear();
				}
			}
		
			//Setting Cluster for each points
			for(int i=0; i<V.size(); i++)
			{
				double point[2] = {V[i][0], V[i][1]};
				double min = pow(point[0]-center[0][0], 2) + pow(point[1]-center[0][1], 2);
				clus[i]=0;
				for(int j=1; j<center.size(); j++)
				{
					double distance = pow(point[0]-center[j][0], 2) + pow(point[1]-center[j][1], 2);
					if(distance < min)
					{
						min = distance;
						clus[i] = j;
					}
				}	
			}

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
		cout << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000000 << " microseconds"<<endl;
		for(int k=0; k<pointnum; k++)
		{
			cout<<clus[k]<<"\n";
		}
		for(int k=0; k<V.size(); ++k)
		{
			cout<<V[k][0]<< ' ';
			cout<<V[k][1]<< ' ';
		}
		cout<<"\n";
	}
}
