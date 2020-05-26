#include <iostream>
#include <string>

#include "FileHandler.h"
#include "MangaSearch.h"

int main() {
	std::cout << "Manga root folder: ";
    std::getline(std::cin, MangaData::rootPath);

	loadData();

	while (true) {
		//Display options
		std::cout << "t <tag>" << std::endl << "\tSearch by tag" << std::endl;
		std::cout << "c <character>" << std::endl << "\tSearch by character" << std::endl;
		std::cout << "a <character>" << std::endl << "\tSearch by artist" << std::endl;
		std::cout << "n <name>" << std::endl << "\tSearch by name" << std::endl;
		std::cout << std::endl;

		//Get command from user
		std::string cmd;
		std::getline(std::cin, cmd);

		//Process command
		switch (cmd[0]) {
			case 't':
				searchManga(SEARCH_TAG, cmd.substr(2, std::string::npos));
				break;
			case 'c':
				searchManga(SEARCH_CHARACTER, cmd.substr(2, std::string::npos));
				break;
			case 'a':
				searchManga(SEARCH_ARTIST, cmd.substr(2, std::string::npos));
				break;
			case 'n':
				searchManga(SEARCH_NAME, cmd.substr(2, std::string::npos));
				break;
		}
	}

	return 0;
}