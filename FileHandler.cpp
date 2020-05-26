#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <time.h>

#include "FileHandler.h"

std::string MangaData::rootPath = "";

template <typename TP>
std::time_t to_time_t(TP tp) {
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

void updateDataFromManga(std::ofstream *out, std::ifstream *in) {
	while (!in->eof()) {
		std::string line;
		std::getline(*in, line);

		if (line != "") {
			*out << line;

			if (!in->eof()) {
				*out << ",";
			}
		}
	}
	*out << std::endl;
}
void compileDataLists() {
	std::cout << "Compiling lists of tags, artists, and characters in one place for easy search" << std::endl;

	std::ifstream mangaListFile;
	mangaListFile.open(FILE_MANGA_NAMES);

	std::ofstream tagFile(FILE_MANGA_TAGS);
	std::ofstream characterFile(FILE_MANGA_CHARACTERS);
	std::ofstream artistFile(FILE_MANGA_ARTISTS);

	while (!mangaListFile.eof()) {
		std::string currManga;
		std::getline(mangaListFile, currManga);

		if (currManga != "") {
			std::cout << "Grabbing tags, artists, and characters from " << currManga << std::endl;

			std::ifstream currTags;
			currTags.open(MangaData::rootPath + "/" + currManga + "/tags.txt");
			updateDataFromManga(&tagFile, &currTags);
			currTags.close();

			std::ifstream currCharacters;
			currCharacters.open(MangaData::rootPath + "/" + currManga + "/characters.txt");
			updateDataFromManga(&characterFile, &currCharacters);
			currCharacters.close();

			std::ifstream currArtists;
			currArtists.open(MangaData::rootPath + "/" + currManga + "/artists.txt");
			updateDataFromManga(&artistFile, &currArtists);
			currArtists.close();
		}
	}

	tagFile.close();
	characterFile.close();
	artistFile.close();
	mangaListFile.close();

	std::cout << std::endl;
}

void loadData() {
	std::cout << "Loading data from root folder" << std::endl;

	std::ifstream dataFile;
	dataFile.open(FILE_MANGA_DATA, std::fstream::in);

	std::string lastModTime;
	std::getline(dataFile, lastModTime);
	if (dataFile.eof()) {
		//Data file was previously empty - generate new data file
		dataFile.close();
		std::ofstream dataOut;
		dataOut.open(FILE_MANGA_DATA, std::fstream::out);

		std::filesystem::file_time_type mangaNamesLastTime = std::filesystem::last_write_time(FILE_MANGA_NAMES);
		std::time_t lastTime = to_time_t(mangaNamesLastTime);
		dataOut << std::to_string(lastTime) << std::endl;

		compileDataLists();
	}
	else {
		//Data file not empty - check last mod time with manganames.txt
		std::filesystem::file_time_type mangaNamesLastTime = std::filesystem::last_write_time(FILE_MANGA_NAMES);
		std::time_t lastTime = to_time_t(mangaNamesLastTime);
		std::string lastTimeStr = std::to_string(lastTime);

		if (lastModTime != lastTimeStr) {
			//Last mod time was after last time this program was run - regen data lists
			compileDataLists();
		}

		//Process data file

		//Update last mod time in data file
		dataFile.close();
		std::ofstream dataOut;
		dataOut.open(FILE_MANGA_DATA, std::fstream::out);
		dataOut << lastTimeStr << std::endl;
	}

	std::cout << std::endl;
}