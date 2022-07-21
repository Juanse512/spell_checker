#ifndef __SPELL_HASHING_H_
#define __SPELL_HASHING_H_
#include "helpers.h"

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed );

unsigned int hash_first(char * word);

Word ** hash_words(char * dictionary[], int counter, int * size);

int find_word(char * word, char * dictionary[], Word ** hashTable, int tableSize, int index);


#endif