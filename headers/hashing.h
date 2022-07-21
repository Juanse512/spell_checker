#ifndef __SPELL_HASHING_H_
#define __SPELL_HASHING_H_
#include "helpers.h"


//MurmurHash2: (void *, int, unsigned int) -> (unsigned int)
// Funcion de hasheo basada en el MurmurHash, fuente: https://sites.google.com/site/murmurhash/
unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed );

//hash_first: (char *) -> (unsigned int)
// Toma una palabra y devuelve su hash
unsigned int hash_first(char * word);

//hash_words: (char **, int, int*) -> (Word**)
// Toma el diccionario y devuelve una tabla hash con las palabras que contiene
// Toma el diccionario, un contador del tamaño de este y un punto a int que indica el tamaño de la nueva tabla hash
Word ** hash_words(char * dictionary[], int counter, int * size);

//find_word: (char *, char **, Word **, int, int) -> (int)
// Busca una palabra en la tabla hash
// Toma una palabra, el diccionario, la tabla hash, el tamaño de esta y un entero que indica la distancia de la palabra a la palabra original, este ultimo argumento 
// es opcional
int find_word(char * word, char * dictionary[], Word ** hashTable, int tableSize, int index);


#endif