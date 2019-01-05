/*
- Viacheslav Verchonov
- 12.30.2018 -
- fileselector_header.hpp
- find all needed info
*/

#pragma once

#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <fstream>
#include <windows.h>

#ifndef HEAD
#define HEAD

using namespace std;
using namespace std::experimental::filesystem;

class FileTime {
public: 
	SYSTEMTIME create;
	SYSTEMTIME accesse;
	SYSTEMTIME write;
};

class SavedInfo {
public:
	vector<int> ID;
	vector<string> location;
	vector<string> dateCreated;
	vector<string> dateAccessed;
	vector<string> dateWrite;
	int count = 1;
};

class UserSettings {
public:
	path folderPath;
	string wordToFind;
	string copyDir;
	SavedInfo info;
	UserSettings() {
		folderPath = canonical("..");
		wordToFind = "";
		copyDir = "C:\\copied";
	}
};

void createFolders(UserSettings& settings);
UserSettings forTxt(UserSettings& settings,path filepath);
UserSettings forExe(UserSettings& settings,path filepath);
UserSettings forCsv(UserSettings& settings, path filepath);

UserSettings getInput(int argc, char* argv[]);
UserSettings searchData(UserSettings& settings);
void getFileTime(path filePath, UserSettings& settings);
void saveInfo(path filePath, FileTime time, UserSettings& settings);
void writeInfo(UserSettings& settings);



#endif
