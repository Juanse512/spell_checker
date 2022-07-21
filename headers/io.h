#ifndef __SPELL_IO_H_
#define __SPELL_IO_H_
#include "helpers.h"

void quit(const char *s);

int readfile(const char *path, char * dictionary[]);

int read_suggestion(Word ** hashTable, char * dictionary[], int dicSize, char * path, int tableSize);


#endif