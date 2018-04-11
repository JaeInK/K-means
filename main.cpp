#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main()
{
	//read input		
	int testnum;
	int i;
	int repeatnum;
	int clusternum;
	int pointnum;
	string str;
	int space;
	
	cout<<"start";
	cin >> testnum;

	for(i=0; i<testnum; i++)
	{	
		cin >> repeatnum;
		cin >> clusternum;
		cin >> pointnum;
		vector< vector<double> > V(pointnum);
		vector<double> tmp;
		for(i=0; i<pointnum; i++)
		{
			cout<<"a";
			cin.clear();
			getline(cin, str);
			//space = str.find(" ");
			space=1;
			cout<<"b";
			cout<<str.length();
			tmp.push_back(atof(str.substr(0, space).c_str()));
			tmp.push_back(atof(str.substr(space, str.size()-space-1).c_str()));
			cout<<"c";
			V.push_back(tmp);
			for(int i=0; i<V.size(); ++i)
				  cout << V[i][0] << ' ';
				  cout << V[i][1] << ' ';
		}
	}
}
