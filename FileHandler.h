#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

#include <string>

#define FILE_MANGA_NAMES MangaData::rootPath + "/manganames.txt"
#define FILE_MANGA_TAGS MangaData::rootPath + "/mangatags.txt"
#define FILE_MANGA_CHARACTERS MangaData::rootPath + "/mangacharacters.txt"
#define FILE_MANGA_ARTISTS MangaData::rootPath + "/mangaartists.txt"
#define FILE_MANGA_DATA MangaData::rootPath + "/data.txt"

struct MangaData {
	static std::string rootPath;
};

void loadData();

#endif