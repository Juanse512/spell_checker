#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "../headers/io.h"
#include "../headers/checker.h"

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed ){
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h = seed ^ len;

	const unsigned char * data = (const unsigned char *)key;

	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		data += 4;
		len -= 4;
	}
	
	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};


	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
} 

unsigned int hash_first(char * word){
    
    int len = strlen(word);
    
    unsigned int hash = MurmurHash2(word, len, SEED_HASH);
    
    return hash;
}


Word ** hash_words(char * dictionary[], int counter, int * size){
    int tableSize = ceil(counter / 0.7); // factor de carga 0.7
    
    Word ** hashTable = malloc(sizeof(Word *) * (tableSize + 1));
    
    clean_array(hashTable, tableSize);
    
    unsigned int firstHash = 0, position = 0;
    
    for(int i = 0; i < counter; i++){
        firstHash = hash_first(dictionary[i]);
        
        position = firstHash % tableSize;
        
        hashTable[position] = insert_word(i, hashTable[position], firstHash, NULL);
    }
    *size = tableSize;
    return hashTable;
}


int find_word(char * word, char * dictionary[], Word ** hashTable, int tableSize, int index){
    unsigned int first_hash = hash_first(word);
    
    unsigned int position = first_hash % tableSize;
    
    int flag = 1;
    
    Word * aux = hashTable[position];

    while(aux != NULL && flag != 0){
        if(aux->hash == first_hash){
            // Si tengo una palabra en word significa que el index indica la distancia
            if(aux->word != NULL){ 
                if(strcmp(word, aux->word) == 0 && aux->index == index){
                    flag = 0;
                }
            }else{
                // Si no indica el indice de la palabra en el diccionario
                if(strcmp(word, dictionary[aux->index]) == 0){

                    flag = 0;
                }
            }
        }
        aux = aux->next;
    }
    return flag == 0 ? 1 : 0;
}
