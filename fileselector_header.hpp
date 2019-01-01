/*
- Viacheslav Verchonov
- 12.30.2018 -
- fileselector_header.hpp
- find all needed info
*/
#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <fstream>

#ifndef HEAD
#define HEAD

using namespace std;
using namespace std::experimental::filesystem;

class UserSettings {
public:
	path folderPath;
	string wordToFind;
	string copyDir;
	UserSettings() {
		folderPath = canonical("..");
		wordToFind = "";
		copyDir = "C:\\copied";
	}
};
void createFolders(UserSettings settings);
UserSettings forTxt(UserSettings settings,path filepath);
UserSettings forExe(UserSettings settings,path filepath);
UserSettings forCsv(UserSettings settings, path filepath);

UserSettings getInput(int argc, char* argv[]);
UserSettings searchData(UserSettings settings);


#endif
