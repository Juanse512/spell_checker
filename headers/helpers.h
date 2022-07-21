#ifndef __SPELL_HELPERS_H_
#define __SPELL_HELPERS_H_
#define MAX_LEN 1000000
#define MAX_LEN_2 10000

typedef struct WordStruct{
  int index;
  char * word;
  unsigned int hash;
  struct WordStruct* next;
} Word;

void clean_array(Word ** hashTable, int counter);

Word * insert_word(int index, Word * word, unsigned int hash, char * wordChar);

void saveWord(char * word, char * dictionary[], int index);

int check_len(char ** array[], int counter, int arraySize);

void free_list(Word * word);

void free_all(char * dictionary[], Word ** hashTable, int tableSize, int dicSize);

void free_accepted(Word ** acceptedWords);

char * parse_word(char * word);

#endif