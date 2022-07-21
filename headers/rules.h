#ifndef __SPELL_RULES_H_
#define __SPELL_RULES_H_
#include "helpers.h"
#include "checker.h"

//apply_rules: (int, char *, char **, Word **, int, Word **, int *, Word **) -> int
// Dada una palabra le aplica las 5 reglas, si la palabra ya fue calculada no la vuelvo a calcular y si no, la guardo en repeatedHash y luego calculo las 5 reglas
int apply_rules(int counter, char * word, char * dictionary[], Word ** hashTable, int tableSize, Word * acceptedWords[], int * acceptedWordsSize, Word ** repeatedHash);

//Las 5 reglas que se le pueden aplicar a una palabra, borrar caracteres, cambiar caracteres, insertar caracteres, cambiar caracteres consecutivos e insertar espacios
// En las primeras 4 si el contador es 0 comparo que la palabra sea correcta, si no llamo a apply_rules con el contador-1 para indicar que se apliquen de nuevo para la distancia
// siguiente
// En la ultima, insertar espacios, separo la palabra y luego comparo si ambas pertenecen al diccionario, no continuo el bucle
// (char *, Word **, int *, int, char **, Word **, int, Word **) -> void
void delete_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash);

void change_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash);

void insert_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash);

void switch_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash);

// insert_spaces: (char *, Word **, int *, int, char **, Word **, int) -> void
void insert_spaces(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize);

#endif