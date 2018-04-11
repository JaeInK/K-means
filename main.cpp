#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	//read input
	string filePath="input.txt";
	
	ifstream openFile(filePath.data());
	
	if( openFile.is_open() )
	{
		string line;
		int testnum;
		int i;
		testnume = getline(openFile,line);

		for(i=0; i<testnum; i++)
		{
			while(getline(openFile, line)){
			cout << line << endl;
		}
		openFile.close();
		}
	}
}
