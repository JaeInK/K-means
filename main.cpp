#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	string filePath="input.txt";
	
	ifstream openFile(filePath.data());
	
	if( openFile.is_open() ){
		string line;
		while(getline(openFile, line)){
			cout << line << endl;
		}
		openFile.close();
	}
}
