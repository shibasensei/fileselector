/*
- Viacheslav Verchonov
- 12.30.2018 - 
- fileselector_main.cpp
- find all needed info
*/
#include "fileselector_header.hpp"

int main(int argc, char * argv[]) {
	UserSettings settings = getInput(argc,argv);
	createFolders(settings);
	settings = searchData(settings);

	//HANDLE hFile1;
	//FILETIME ftCreate,access,write;
	//SYSTEMTIME stUTC, stUTC1, stUTC2;
	//hFile1 = CreateFile("C:\\copied\\txt\\text.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//if (hFile1 == INVALID_HANDLE_VALUE)
	//{
	//	printf("Could not open file, error %ul\n", GetLastError());
	//	return -1;
	//}

	//if (!GetFileTime(hFile1, &ftCreate, &access, &write))
	//{
	//	printf("Something wrong!\n");
	//	return FALSE;
	//}
	//FileTimeToSystemTime(&ftCreate, &stUTC);
	//FileTimeToSystemTime(&access, &stUTC1);
	//FileTimeToSystemTime(&write, &stUTC2);
	//cout << stUTC1.wDay << endl;

}