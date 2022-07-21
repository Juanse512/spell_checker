#ifndef __SPELL_CHECKER_H_
#define __SPELL_CHECKER_H_
#include "helpers.h"
#include "rules.h"

void insert_word_result(char * word, Word ** acceptedWords, int * acceptedWordsSize);

void pre_check(char * word, char * dictionary[], Word ** hashTable, int tableSize, Word ** acceptedWords, int * acceptedWordsCounter);

Word ** suggest_word(char * word, char * dictionary[], int dicSize, Word ** hashTable, int tableSize, int * acceptedWordsCounter);

void check_word(char * word, char * dictionary[], Word** hashTable, int tableSize, int dicSize, int line);

#endif