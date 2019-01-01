/*
- Viacheslav Verchonov
- 12.30.2018 - 
- fileselector_main.cpp
- find all needed info
*/
#include "fileselector_header.hpp"

#include <fstream>

int main(int argc, char * argv[]) {
	//ifstream file;
	//string line;
	//file.open("C:\\Users\\Vyacheslav\\Documents\\Docs\\Kiev\\test\\test.csv");
	//if (!file) {
	//	cerr << "error" << endl;
	//	exit(EXIT_FAILURE);
	//}
	//while (getline(file,line,',')) {
	//	cout << line << endl;
	//}
	//file.close();
	UserSettings settings = getInput(argc,argv);
	createFolders(settings);
	cout << "path = " << settings.folderPath << endl;
	cout << "word = " << settings.wordToFind << endl;
	settings = searchData(settings);
}