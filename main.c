#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define MAX_LEN 1000000


typedef struct WordStruct{
  int index;
  char * word;
  unsigned int hash;
  struct WordStruct* next;
} Word;

int apply_rules(int counter, char * word, char * dictionary[], Word ** hash_table, int table_size, Word * acceptedWords[], int * acceptedWordsSize);




static inline void quit(const char *s)
{
	perror(s);
	exit(1);
}

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed )
{
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

unsigned int hash_first(char * word)
{
    
    int len = strlen(word);
    double res = 0;
    unsigned int hash = MurmurHash2(word, len, 13);
    return hash;
}

void clean_array(Word ** hash_table, int counter)
{
    for(int i = 0; i < counter; i++)
    {
        hash_table[i] = NULL;
    }
}


Word * insert_word(int index, Word * word, unsigned int hash)
{
    Word * newWord = malloc(sizeof(Word));
    newWord->index = index;
    newWord->next = NULL;
    newWord->hash = hash;
    if(word == NULL){
        word = newWord;
    }else{
        Word * aux = word;
        while(aux != NULL && aux->next){
            aux = aux->next;
        }
        aux->next = newWord;
    }
    return word;
}

void insert_word_result(char * word, Word ** acceptedWords, int * acceptedWordsSize){
    if(*acceptedWordsSize >= 5) return;
    int flag = 0;
    unsigned int wordHash = hash_first(word);
    for(int i = 0; i < *acceptedWordsSize; i++){
        if(acceptedWords[i] != NULL){
            if(acceptedWords[i]->hash == wordHash){
                flag = 1;
            }
        }
    }
    if(flag == 0){
        acceptedWords[*acceptedWordsSize] = malloc(sizeof(Word));
        acceptedWords[*acceptedWordsSize]->hash = wordHash;
        acceptedWords[*acceptedWordsSize]->word = malloc(sizeof(char) * (strlen(word) + 1));
        memcpy(acceptedWords[*acceptedWordsSize]->word, word, strlen(word) + 1); 
        (*acceptedWordsSize)++;
    }
    return;
}

Word ** hash_words(char * dictionary[], int counter, int * size)
{
    int table_size = ceil(counter / 0.7);
    Word ** hash_table = malloc(sizeof(Word *) * (table_size + 1));
    
    clean_array(hash_table, table_size);
    
    unsigned int first_hash = 0, second_hash = 0, position = 0, collision = 0;
    
    for(int i = 0; i < counter; i++)
    {
        first_hash = hash_first(dictionary[i]);
        // second_hash = hash_second(dictionary[i], table_size);
        
        position = first_hash % table_size;
        
        hash_table[position] = insert_word(i, hash_table[position], first_hash);
    }
    *size = table_size;
    return hash_table;
}

void saveWord(char * word, char * dictionary[], int index)
{
    dictionary[index] = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(dictionary[index], word);
}



int readfile(const char *path, char * dictionary[])
{
	char aux[100];
	
    FILE *f = fopen(path, "rb");
	
    int c, i = 0, counter = 0;
	
    if (f == NULL)
        quit("readfile.fopen");
    
    int flag = 1;
	
    while (flag) {
        c = getc(f);
        
        if(c == '\n' || c == EOF){
            aux[i - 1] = '\0';
        
            saveWord(aux, dictionary, counter);
        
            counter++;
        
            i = 0;
        
            if(c == EOF) flag = 0;
        }else{
            aux[i++] = c;
        }
	}
	
    fclose(f);
    
    return counter;
}

int find_word(char * word, char * dictionary[], Word ** hash_table, int table_size)
{
    unsigned int first_hash = hash_first(word);
    unsigned int position = first_hash % table_size;
    int second_hash = 0, collision = 1, flag = 1;
    
    // second_hash = hash_second(word, table_size);
    Word * aux = hash_table[position];
    while(aux != NULL && flag != 0)
    {
        if(aux->hash == first_hash){
            if(strcmp(word, dictionary[aux->index]) == 0){
                flag = 0;
            }
        }
        aux = aux->next;
    }
    // printf("%d\n", flag);
    return flag == 0 ? 1 : 0;
}

int check_len(char ** array[], int counter, int array_size)
{
    int newSize = array_size;
    if(array_size <= counter){
        newSize = (newSize * 3);
        // printf("IN HERE %d %d\n", counter, newSize);
        *array = realloc(*array, sizeof(char *) * (newSize));
    }
    return newSize;
}

void switch_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size)
{
    int len = strlen(word);
    char aux;
    char * wordRule;
    for(int i = 0; i < len - 1; i++)
    {
        wordRule = malloc(sizeof(char) * (len + 2));
        
        memcpy(wordRule, word, len + 1);
        
        aux = wordRule[i];
        
        wordRule[i] = wordRule[i + 1];
        
        wordRule[i + 1] = aux;
        if(counter == 0){
            if(find_word(wordRule, dictionary, hash_table, table_size)){
                // printf("%s\n", wordRule);
                insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
            }
        }else{
            apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize);         
        }
        free(wordRule);

    }
    return;
}
void insert_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size)
{
    int len = strlen(word);
    char * wordRule;
    // printf("%d\n", counter);
    for(int i = 0; i <= len; i++){
        for(char j = 97; j < 123; j++){
            wordRule = malloc(sizeof(char) * (len + 3));

            memcpy(wordRule, word, (len - (len - i)) + 1);
            memcpy(wordRule + (i + 1), word + i, (len - i) + 1);
            
            wordRule[i] = j;
            
            if(counter == 0){
                if(find_word(wordRule, dictionary, hash_table, table_size)){
                    insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                    // printf("%s\n", wordRule);
                }
            }else{
                apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize);
            }
            free(wordRule);
        }
    }
    return;
}

void change_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size)
{
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i < len; i++){
        for(char j = 97; j < 123; j++){
            // printf("%d\n", counter);
            wordRule = malloc(sizeof(char) * (len + 2));
            memcpy(wordRule, word, len + 1);
            wordRule[i] = j;

            if(counter == 0){
                if(find_word(wordRule, dictionary, hash_table, table_size)){
                    insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                    // printf("%s\n", wordRule);
                }
            }else{
                apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize);
            }
            free(wordRule);
        }
    }
    return;
}

void delete_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size)
{
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i < len; i++){
        wordRule = malloc(sizeof(char) * (len + 2));
        
        memcpy(wordRule, word, (len - (len - i)) + 1);
        memcpy(wordRule + i, word + (i + 1), (len - i) + 1);

        if(counter == 0){
            if(find_word(wordRule, dictionary, hash_table, table_size)){
                insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                // printf("%s\n", wordRule);
            }
        }else{
            apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize);
        }
        free(wordRule);
    }
    return;
}

void insert_spaces(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size)
{
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        char * firstWord = malloc(sizeof(char) * ((len - (len - i)) + 1));
        char * secondWord = malloc(sizeof(char) * ((len - i) + 1));

        memcpy(firstWord, word, (len - (len - i)) + 1);
        firstWord[(len - (len - i))] = '\0';
        memcpy(secondWord, word + i, (len - i) + 1);
        secondWord[(len - i)] = '\0';
        
        
        if(find_word(firstWord, dictionary, hash_table, table_size) && find_word(secondWord, dictionary, hash_table, table_size)){
            insert_word_result(firstWord, acceptedWords, acceptedWordsSize);
            insert_word_result(secondWord, acceptedWords, acceptedWordsSize);
            // printf("%s\n", wordRule);
        }
        free(firstWord);
        free(secondWord);

        
    }
    return;
}


int apply_rules(int counter, char * word, char * dictionary[], Word ** hash_table, int table_size, Word * acceptedWords[], int * acceptedWordsSize)
{
    if(*acceptedWordsSize >= 5) return 0;
    switch_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size);
    insert_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size);
    change_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size);
    delete_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size);
    insert_spaces(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size);
    return counter;
}

// 
int pre_check(char * word, char * dictionary[], Word ** hash_table, int table_size, Word ** acceptedWords, int * acceptedWordsCounter)
{
    
    int distance = 0;

    while(distance < 3 && *acceptedWordsCounter < 5){
        apply_rules(distance, word, dictionary, hash_table, table_size, acceptedWords, acceptedWordsCounter);
        distance++;
    }
    for(int i = 0; i < *acceptedWordsCounter; i++){
        printf("%s\n", acceptedWords[i]->word);
    }

}

void free_list(Word * word){
    if(word == NULL)
        return;
    Word * next = word->next;
    free(word);
    free_list(next);
}

void free_all(char * dictionary[], Word ** acceptedWords, Word ** hashTable, int tableSize, int dicSize)
{   
    printf("%d %d\n", dicSize, tableSize);
    for(int i = 0; i < dicSize; i++){
        free(dictionary[i]); //free elements inside
    }
    for(int i = 0; i < 6; i++){
        if(acceptedWords[i] != NULL){
            free(acceptedWords[i]->word);
            free(acceptedWords[i]);
        }
    }
    free(acceptedWords);
    for(int i = 0; i < tableSize; i++){
        free_list(hashTable[i]);
    }
    free(hashTable);
}

int main()
{
    char * dictionary[MAX_LEN];
    int tableSize = 0, acceptedWordsCounter = 0;
    int dicSize = readfile("diccionario.txt", dictionary);
    Word ** acceptedWords = malloc(sizeof(char *) * 6);
    clean_array(acceptedWords, 6);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    pre_check("eugenio\0", dictionary, hashTable, tableSize, acceptedWords, &acceptedWordsCounter);
    free_all(dictionary, acceptedWords, hashTable, tableSize, dicSize);
    return 0;
}