#include <algorithm>
#include <iostream>
#include <fstream>

#include "MangaSearch.h"
#include "FileHandler.h"

//computeTransFun and patternMatch are modified versions of code from GeeksForGeeks
//https://www.geeksforgeeks.org/pattern-searching-set-5-efficient-constructtion-of-finite-automata/

#define NO_OF_CHARS 256
void computeTransFun(std::string pat, int M, int **TF) {
    int i, lps = 0, x;

    // Fill entries in first row 
    for (x = 0; x < NO_OF_CHARS; x++)
        TF[0][x] = 0;
    TF[0][pat[0]] = 1;

    // Fill entries in other rows 
    for (i = 1; i <= M; i++) {
        // Copy values from row at index lps 
        for (x = 0; x < NO_OF_CHARS; x++)
            TF[i][x] = TF[lps][x];

        // Update the entry corresponding to this character 
        TF[i][pat[i]] = i + 1;

        // Update lps for next row to be filled 
        if (i < M)
            lps = TF[lps][pat[i]];
    }
}
bool patternMatch(std::string src, std::string pat, int **TF) {
	//Handle basic cases
	if (src.length() < pat.length()) {
		return false;
	}
	else if (src.length() == pat.length()) {
		return src == pat;
	}

	//Pattern searching algorithm using finite automata in O(N) time, where N is the length of the string being searched
	int M = pat.length();
	int N = src.length();

	// process text over FA. 
	int i, j = 0;
	for (i = 0; i < N; i++) {
		j = TF[j][src[i]];
		if (j == M) {
			return true;
		}
	}

	return false;
}

void searchMangaName(std::string str) {
	//Transition table for pattern search
	int M = str.length();
	int **TF = new int *[M + 1];
	for (int i = 0; i < M + 1; i++) {
		TF[i] = new int[NO_OF_CHARS];
	}
	computeTransFun(str, M, TF);

	//Search for matches
	std::ifstream names;
	names.open(FILE_MANGA_NAMES);

	while (!names.eof()) {
		std::string currName;
		std::getline(names, currName);

		bool match = patternMatch(currName, str, TF);
		if (match) {
			std::cout << "Match: " << currName << std::endl;
		}
	}

	for (int i = 0; i < M; i++) {
		delete[] TF[i];
	}
	delete[] TF;

	names.close();
}
void searchMangaTag(std::string str) {
	//Transition table for pattern search
	int M = str.length();
	int **TF = new int *[M + 1];
	for (int i = 0; i < M + 1; i++) {
		TF[i] = new int[NO_OF_CHARS];
	}
	computeTransFun(str, M, TF);

	//Search for matches
	std::ifstream tags, names;
	tags.open(FILE_MANGA_TAGS);
	names.open(FILE_MANGA_NAMES);

	while (!tags.eof()) {
		std::string currTag, currName;
		std::getline(tags, currTag);
		std::getline(names, currName);

		bool match = patternMatch(currTag, str, TF);
		if (match) {
			std::cout << "Match: " << currName << std::endl;
		}
	}

	for (int i = 0; i < M; i++) {
		delete[] TF[i];
	}
	delete[] TF;

	tags.close();
	names.close();
}
void searchMangaCharacter(std::string str) {
	//Transition table for pattern search
	int M = str.length();
	int **TF = new int *[M + 1];
	for (int i = 0; i < M + 1; i++) {
		TF[i] = new int[NO_OF_CHARS];
	}
	computeTransFun(str, M, TF);

	//Search for matches
	std::ifstream characters, names;
	characters.open(FILE_MANGA_CHARACTERS);
	names.open(FILE_MANGA_NAMES);

	while (!characters.eof()) {
		std::string currCharacter, currName;
		std::getline(characters, currCharacter);
		std::getline(names, currName);

		bool match = patternMatch(currCharacter, str, TF);
		if (match) {
			std::cout << "Match: " << currName << std::endl;
		}
	}

	for (int i = 0; i < M; i++) {
		delete[] TF[i];
	}
	delete[] TF;

	characters.close();
	names.close();
}
void searchMangaArtist(std::string str) {
	//Transition table for pattern search
	int M = str.length();
	int **TF = new int *[M + 1];
	for (int i = 0; i < M + 1; i++) {
		TF[i] = new int[NO_OF_CHARS];
	}
	computeTransFun(str, M, TF);

	//Search for matches
	std::ifstream artists, names;
	artists.open(FILE_MANGA_ARTISTS);
	names.open(FILE_MANGA_NAMES);

	while (!artists.eof()) {
		std::string currArtist, currName;
		std::getline(artists, currArtist);
		std::getline(names, currName);

		bool match = patternMatch(currArtist, str, TF);
		if (match) {
			std::cout << "Match: " << currName << std::endl;
		}
	}

	for (int i = 0; i < M; i++) {
		delete[] TF[i];
	}
	delete[] TF;

	artists.close();
	names.close();
}

void searchManga(short type, std::string query) {
	//Replace spaces with -
	std::replace(query.begin(), query.end(), ' ', '-');

	std::cout << "Searching for " << query;

	switch (type) {
		case SEARCH_NAME:
			std::cout << " as a name" << std::endl;
			searchMangaName(query);
			break;
		case SEARCH_TAG:
			std::cout << " as a tag" << std::endl;
			searchMangaTag(query);
			break;
		case SEARCH_CHARACTER:
			std::cout << " as a character" << std::endl;
			searchMangaCharacter(query);
			break;
		case SEARCH_ARTIST:
			std::cout << " as an artist" << std::endl;
			searchMangaArtist(query);
			break;
	}

	std::cout << std::endl;
}