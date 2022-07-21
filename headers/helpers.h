#ifndef __SPELL_HELPERS_H_
#define __SPELL_HELPERS_H_
#define MAX_LEN 1000000
#define MAX_LEN_2 10000
#define SEED_HASH 13
//Word:
// index: indica la posicion de la palabra en el diccionario en la tabla hash original y la distancia en la tabla hash de palabras ya calculadas
// word: contiene la palabra, no se una en la tabla hash original del diccionario
// hash: hash de la palabra
// next: puntero al Word siguiente
typedef struct WordStruct{
  int index;
  char * word;
  unsigned int hash;
  struct WordStruct* next;
} Word;

//clean_array: (Word **, int) -> ()
// Toma un array de punteros y los pone a NULL
void clean_array(Word ** hashTable, int counter);

//insert_word: (int, Word *,unsigned int, char *) -> (Word*)
// Toma una palabra o el indice de una y la coloca al final de la Word que le pasamos, devuelve la Word actualizada
Word * insert_word(int index, Word * word, unsigned int hash, char * wordChar);

//save_word: (char *, char **, int) -> ()
// Guarda una palabra en el array que le pasamos, en la posicion dada
void save_word(char * word, char * dictionary[], int index);

// save_word: (char ***, int, int) -> (int)
// Dado el puntero de un array de punteros y un contador, si el contador es mayor al tamaño del array, se triplica el tamaño de este y devuelve el tamaño
int check_len(char ** array[], int counter, int arraySize);

// free_list: (Word *) -> ()
// Libera la lista enlazada de un Word
void free_list(Word * word);

// free_all: (char **, Word **, int, int) -> ()
// Libera el diccionario y la tabla hash
void free_all(char * dictionary[], Word ** hashTable, int tableSize, int dicSize);

// free_accepted: (Word **) -> ()
// Libera la lista de palabras aceptadas
void free_accepted(Word ** acceptedWords);

// parse_word: (char *) -> ()
// Dada una palabra, la pasa a minuscula y saca todos los caracteres especiales
char * parse_word(char * word);

#endif