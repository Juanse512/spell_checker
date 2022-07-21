#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "../headers/io.h"
#include "../headers/checker.h"

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed ){
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value

	unsigned int h = seed ^ len;

	// Mix 4 bytes at a time into the hash

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
	
	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
} 

//hashing
unsigned int hash_first(char * word){
    
    int len = strlen(word);
    unsigned int hash = MurmurHash2(word, len, 13);
    return hash;
}


//hashing
Word ** hash_words(char * dictionary[], int counter, int * size){
    int table_size = ceil(counter / 0.7);
    Word ** hash_table = malloc(sizeof(Word *) * (table_size + 1));
    
    clean_array(hash_table, table_size);
    
    unsigned int first_hash = 0, position = 0;
    
    for(int i = 0; i < counter; i++)
    {
        first_hash = hash_first(dictionary[i]);
        
        position = first_hash % table_size;
        
        hash_table[position] = insert_word(i, hash_table[position], first_hash, NULL);
    }
    *size = table_size;
    return hash_table;
}


//hashing
int find_word(char * word, char * dictionary[], Word ** hashTable, int tableSize, int index){
    unsigned int first_hash = hash_first(word);
    unsigned int position = first_hash % tableSize;
    int flag = 1;
    
    // second_hash = hash_second(word, tableSize);
    Word * aux = hashTable[position];

    while(aux != NULL && flag != 0)
    {
        if(aux->hash == first_hash){
            if(aux->word != NULL){
                if(strcmp(word, aux->word) == 0 && aux->index == index){
                    flag = 0;
                }
            }else{
                if(strcmp(word, dictionary[aux->index]) == 0){
                    flag = 0;
                }
            }
            // flag = 0;
        }
        aux = aux->next;
    }
    // printf("%d\n", flag);
    return flag == 0 ? 1 : 0;
}
