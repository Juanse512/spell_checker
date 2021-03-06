#ifndef __SPELL_IO_H_
#define __SPELL_IO_H_
#include "helpers.h"

void quit(const char *s);

//readfile: (const char *, char ***) -> (int)
// Dado un path y un array lee un archivo y guarda sus palabras en el array, devuelve la cantidad de palabras leidas
int readfile(const char *path, char *** dictionaryP);
//read_suggestion: (Word **, char **, int, char *, int, char *) -> (int)
// Lee un archivo y por cada palabra, la parsea y llama a check_word para ver si es valida o si tiene que corregirse, ademas crea un array de punteros de Word donde
// se guardan las palabras ya corregidas para no volver a calcularlas
int read_suggestion(Word ** hashTable, char * dictionary[], int dicSize, char * path, int tableSize, char * outPath);


#endif