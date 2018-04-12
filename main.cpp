#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

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
	for(int i=0; i<testnum; i++)
	{	
		cout<<"repeat";
		cin >> repeatnum;
		cout<<repeatnum;
		cin >> clusternum;
		cout<<clusternum;
		cin >> pointnum;
		cout<<pointnum<<' ';
		vector< vector<double> > V;
		for(int j=0; j<pointnum; j++)
		{
			cin>>str1;
			cin>>str2;
			vector<double> tmp;
			tmp.push_back(atof(str1.c_str()));
			tmp.push_back(atof(str2.c_str()));
			V.push_back(tmp);
		}

		//K-Means-Clustering

		for(int k=0; k<V.size(); ++k)
		{
			cout<<V[k][0]<< ' ';
			cout<<V[k][1]<< ' ';
		}
		cout<<"\n";
	}
}
