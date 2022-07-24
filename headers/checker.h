#ifndef __SPELL_CHECKER_H_
#define __SPELL_CHECKER_H_
#include "helpers.h"
#include "rules.h"

// insert_word_result (char*, Word **, int *) -> ()
// Inserta una palabra en el array de palabras aceptadas y actualiza el tamaño de este, ademas se asegura de no guardar palabras repetidas usando el hash de la palabra
// que le pasamos

void insert_word_result(char * word, Word ** acceptedWords, int * acceptedWordsSize);

// pre_check (char*, char **, Word **, int, Word**, int*) -> ()
// Se encarga de aplicar las reglas hasta 3 veces o hasta que encontremos 5 sugerencias para una palabra dada.
// Toma una palabra, el diccionario, la tabla hash donde guardamos las palabras, el tamaño de esta tabla, un array con las palabras aceptadas y el contador de palabras aceptadas
// Ademas declara y libera una nueva tabla hash donde vamos a guardar las palabras ya calculadas

void pre_check(char * word, char * dictionary[], Word ** hashTable, int tableSize, Word ** acceptedWords, int * acceptedWordsCounter);

// suggest_word (char*, char **, int, Word **, int, Word**, int*) -> (Word **)
// Se encarga de alocar memoria para un array de resultados y luego llama a pre_check para conseguir las sugerencias, devuelve este array de sugerencias.
// Ademas modifica el contador de palabras aceptadas
Word ** suggest_word(char * word, char * dictionary[], int dicSize, Word ** hashTable, int tableSize, int * acceptedWordsCounter);

// check_word (char*, char **, Word **, int, int, int, char *, Word**) -> ()
// Toma una palabra, revisa que sea incorrecta y llama a las funciones necesarias para conseguir sugerencias, luego las imprime
// Toma una palabra, el diccionario, la tabla hash, el tamaño de la tabla y del diccionario y la linea en la que se encuentra la palabra, ademas toma el path del archivo de salida
// y un array con las palabras ya calculadas
void check_word(char * word, char * dictionary[], Word** hashTable, int tableSize, int dicSize, int line, char * outPath, Word ** repeatedWord);

#endif