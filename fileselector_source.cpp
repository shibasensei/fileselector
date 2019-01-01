/*
- Viacheslav Verchonov
- 12.30.2018 -
- fileselector_source.cpp
- find all needed info
*/
#include "fileselector_header.hpp"

UserSettings forTxt(UserSettings settings,path filepath) {
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
				break;
			}
		}
	}
	return settings;
}

UserSettings forCsv(UserSettings settings, path filepath) {
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
		if (settings.wordToFind == words[x]) {
			if (copy_file(filepath, temp / filepath.filename(), copy_options::skip_existing)) {
				break;
			}
		}
	}
	return settings;
}

UserSettings forExe(UserSettings settings, path filepath) {
	string temp = settings.copyDir + "\\exe";
	if (copy_file(filepath, temp / filepath.filename(), copy_options::skip_existing)) {

	}
	return settings;
}

void createFolders(UserSettings settings) {
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

UserSettings searchData(UserSettings settings) {
	path temp;
			for (auto & p : recursive_directory_iterator(settings.folderPath))
			{	//if file check for requirments
				if (!is_directory(status(p))) {
					temp = p;
					if (temp.extension() == ".exe")
						forExe(settings,temp);
					if (temp.extension() == ".txt")
						forTxt(settings,temp);
				}
			}	
	return settings;
}



