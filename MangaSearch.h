#ifndef _MANGA_SEARCH_H
#define _MANGA_SEARCH_H

#include <string>

#define SEARCH_TAG 0
#define SEARCH_CHARACTER 1
#define SEARCH_ARTIST 2
#define SEARCH_NAME 3

void searchManga(short type, std::string query);

#endif