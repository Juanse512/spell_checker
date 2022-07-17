#ifndef __SPELL_RULES_H_
#define __SPELL_RULES_H_
#include "helpers.h"
#include "checker.h"

int apply_rules(int counter, char * word, char * dictionary[], Word ** hash_table, int table_size, Word * acceptedWords[], int * acceptedWordsSize, Word ** repeatedHash);

void insert_spaces(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size);

void delete_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash);

void change_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash);

void insert_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash);

void switch_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash);


#endif