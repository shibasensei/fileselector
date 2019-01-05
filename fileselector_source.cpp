/*
- Viacheslav Verchonov
- 12.30.2018 -
- fileselector_source.cpp
- find all needed info
*/
#include "fileselector_header.hpp"


void saveInfo(path filePath, FileTime time, UserSettings& settings) {
	settings.info.ID.push_back(settings.info.count);
	settings.info.count++;
	ostringstream tempCreated;
	ostringstream tempAccessed;
	ostringstream tempWrite;
	tempCreated << time.create.wDay << "." << time.create.wMonth << "." << time.create.wYear << " | " << time.create.wHour << ":" << time.create.wMinute ;
	settings.info.dateCreated.push_back(tempCreated.str());
	tempAccessed << time.accesse.wDay << "." << time.accesse.wMonth << "." << time.accesse.wYear << " | " << time.accesse.wHour << ":" << time.accesse.wMinute;
	settings.info.dateAccessed.push_back(tempAccessed.str());
	tempWrite << time.write.wDay << "." << time.write.wMonth << "." << time.write.wYear << " | " << time.write.wHour << ":" << time.write.wMinute;
	settings.info.dateWrite.push_back(tempWrite.str());
	settings.info.location.push_back(filePath.u8string());
}

void writeInfo(UserSettings& settings) {
	ofstream o;
	o.open("C:\\copied\\copiedinfo.csv");
	o << "ID,Location,Create Time,Access Time,Write Time\n";
	for (unsigned int x = 0; x < settings.info.ID.size(); x++) {
		o << settings.info.ID[x] << "," + settings.info.location[x] <<  "," << settings.info.dateCreated[x] << "," << settings.info.dateAccessed[x]<<  "," << settings.info.dateWrite[x] << ",\n";
	}
	o.close();
}

void getFileTime( path filePath, UserSettings& settings) {
	HANDLE hFile1;
	FILETIME ftCreate, ftAccessed, ftWrite;
	FileTime time;
	hFile1 = CreateFile(filePath.u8string().c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile1 == INVALID_HANDLE_VALUE)
	{
		printf("Could not open file, error %ul\n", GetLastError());
		exit(EXIT_FAILURE);
	}
	if (!GetFileTime(hFile1, &ftCreate, &ftAccessed, &ftWrite))
	{
		printf("Something wrong!\n");
		exit(EXIT_FAILURE);
	}
	FileTimeToSystemTime(&ftCreate, &time.create);
	FileTimeToSystemTime(&ftAccessed, &time.accesse);
	FileTimeToSystemTime(&ftWrite, &time.write);
	saveInfo(filePath, time,settings);
	
}

UserSettings forTxt(UserSettings& settings,path filepath) {
	string temp = settings.copyDir + "\\txt";
	vector<string> words;
	string word;
	ifstream file;
	file.open(filepath);
	if (!file)
	{
		cerr << "Cannot open file:\n" << filepath <<endl;
		exit(EXIT_FAILURE);
	}
	while (file >> word)
		words.push_back(word);
	file.close();
	for (unsigned int x = 0; x < words.size();x++) {
		if (settings.wordToFind == words[x]) {
			if (copy_file(filepath, temp / filepath.filename(), copy_options::skip_existing)) {
				getFileTime(filepath,settings);
				break;
			}
		}
	}
	return settings;
}

UserSettings forCsv(UserSettings& settings, path filepath) {
	string temp = settings.copyDir + "\\csv";
	vector<string> words;
	string word;
	ifstream file;
	file.open(filepath);
	if (!file)
	{
		cerr << "Cannot open file:\n" << filepath << endl;
		exit(EXIT_FAILURE);
	}
	while (getline(file, word, ','))
		words.push_back(word);
	file.close();
	for (unsigned int x = 0; x < words.size(); x++) {
		//if (settings.wordToFind == words[x]) {
			if (copy_file(filepath, temp / filepath.filename(), copy_options::skip_existing)) {
				getFileTime(filepath, settings);
				break;
			}
		//}
	}
	return settings;
}

UserSettings forExe(UserSettings& settings, path filepath) {
	string temp = settings.copyDir + "\\exe";
	if (copy_file(filepath, temp / filepath.filename(), copy_options::skip_existing)) {
		getFileTime(filepath,settings);
	}
	return settings;
}

void createFolders(UserSettings& settings) {
	create_directories(settings.copyDir);
	create_directory(settings.copyDir + "\\txt");
	create_directory(settings.copyDir + "\\csv");
	create_directory(settings.copyDir + "\\exe");
}

UserSettings getInput(int argc, char* argv[]) {
	//create class to hold info
	UserSettings settings;
	//check for args
	if (argc < 2 || argc > 3) {
		cerr << "Wrong parametrs. \nExample: .exe path word" <<endl;
		exit(EXIT_FAILURE);
	}
	settings.folderPath = argv[1];
	settings.wordToFind = argv[2];
	//check if folder exists
	if (!exists(settings.folderPath)) {
		cerr << "Path does not exist:\n"<< settings.folderPath << endl;
		exit(EXIT_FAILURE);
	}
	return settings;
}

UserSettings searchData(UserSettings& settings) {
	path temp;
			for (auto & p : recursive_directory_iterator(settings.folderPath))
			{	//if file check for requirments
				if (!is_directory(status(p))) {
					temp = p;
					if (temp.extension() == ".exe")
						forExe(settings,temp);
					if (temp.extension() == ".txt")
						forTxt(settings,temp);
					if (temp.extension() == ".csv") {
						forCsv(settings, temp);					
					}
				}
			}	
			writeInfo(settings);
	return settings;
}



