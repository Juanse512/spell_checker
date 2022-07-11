#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define MAX_LEN 1000000

typedef struct WordStruct{
  int index;
  unsigned int hash;
  struct WordStruct* next;
} Word;


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

unsigned int hash_first(char * word, int counter)
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

Word ** hash_words(char * dictionary[], int counter, int * size)
{
    int table_size = ceil(counter / 0.7);
    Word ** hash_table = malloc(sizeof(Word *) * (table_size + 1));
    
    clean_array(hash_table, table_size);
    
    unsigned int first_hash = 0, second_hash = 0, position = 0, collision = 0;
    
    for(int i = 0; i < counter; i++)
    {
        first_hash = hash_first(dictionary[i], table_size);
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
    unsigned int first_hash = hash_first(word, table_size);
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

int switch_characters(char * word, char ** result_arrayP[], int counter, int * array_size)
{
    int len = strlen(word);
    char aux;
    char ** result_array = *result_arrayP;
    for(int i = 0; i < len - 1; i++)
    {
        *array_size = check_len(result_arrayP, counter, *array_size);
        result_array = *result_arrayP;
        result_array[counter] = malloc(sizeof(char) * (len + 1));
        
        memcpy(result_array[counter], word, len + 1);
        
        aux = result_array[counter][i];
        
        result_array[counter][i] = result_array[counter][i + 1];
        
        result_array[counter][i + 1] = aux;
        
        counter++;
    }
    return counter;
}
int insert_characters(char * word, char ** result_arrayP[], int counter, int * array_size)
{
    int len = strlen(word);
    char ** result_array = *result_arrayP;
    for(int i = 0; i <= len; i++){
        for(char j = 97; j < 123; j++){
            *array_size = check_len(result_arrayP, counter, *array_size);
            result_array = *result_arrayP;
            result_array[counter] = malloc(sizeof(char) * (len + 2));

            memcpy(result_array[counter], word, (len - (len - i)) + 1);
            memcpy(result_array[counter] + (i + 1), word + i, (len - i) + 1);
            
            result_array[counter][i] = j;

            // printf("%s\n", result_array[counter]);

            counter++;
        }
    }
    return counter;
}

int change_characters(char * word, char ** result_arrayP[], int counter, int * array_size)
{
    int len = strlen(word);
    char ** result_array = *result_arrayP;
    for(int i = 0; i < len; i++){
        for(char j = 97; j < 123; j++){
            *array_size = check_len(result_arrayP, counter, *array_size);
            result_array = *result_arrayP;
            // printf("%d\n", counter);
            result_array[counter] = malloc(sizeof(char) * (len + 1));
            memcpy(result_array[counter], word, len + 1);
            result_array[counter][i] = j;

            // printf("%s\n", result_array[counter]);

            counter++;
        }
    }
    return counter;
}

int delete_characters(char * word, char ** result_arrayP[], int counter, int * array_size)
{
    char ** result_array = *result_arrayP;
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        *array_size = check_len(result_arrayP, counter, *array_size);
        result_array = *result_arrayP;
        result_array[counter] = malloc(sizeof(char) * (len));
        
        memcpy(result_array[counter], word, (len - (len - i)) + 1);
        memcpy(result_array[counter] + i, word + (i + 1), (len - i) + 1);

        // printf("%s\n", result_array[counter]);

        counter++;
    }
    return counter;
}

int insert_spaces(char * word, char ** result_arrayP[], int counter, int * array_size, char * dictionary[], Word ** hash_table, int table_size)
{
    char ** result_array = *result_arrayP;
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        char * firstWord = malloc(sizeof(char) * ((len - (len - i)) + 1));
        char * secondWord = malloc(sizeof(char) * ((len - i) + 1));

        memcpy(firstWord, word, (len - (len - i)) + 1);
        firstWord[(len - (len - i))] = '\0';
        memcpy(secondWord, word + i, (len - i) + 1);
        secondWord[(len - i)] = '\0';
        
        // printf("%s %s\n", firstWord, secondWord);

        *array_size = check_len(result_arrayP, counter, *array_size);
        result_array = *result_arrayP;
        if(find_word(firstWord, dictionary, hash_table, table_size) && find_word(secondWord, dictionary, hash_table, table_size)){
            *array_size = check_len(&result_array, counter + 1, *array_size);
            result_array[counter] = firstWord;
            result_array[counter + 1] = secondWord;
            counter += 2;
        }

        
    }
    return counter;
}

int apply_rules(int counter, char * word, char * dictionary[], Word ** hash_table, int table_size, char ** result_array[], int * result_array_size, char ** acceptedWords[], int * acceptedWordsSize, int * counterAcc)
{
    // printf("switch\n");
    int counterAccT = 0;
    char ** dOneT = *result_array;
    char ** AccT = *acceptedWords;
    int dOneTsize = *result_array_size, AcctSize = *acceptedWordsSize;
    counter = switch_characters(word, &dOneT, counter, &dOneTsize);
    // printf("insert\n");
    counter = insert_characters(word, &dOneT, counter, &dOneTsize);
    // printf("change\n");
    counter = change_characters(word, &dOneT, counter, &dOneTsize);
    // printf("delete\n");
    counter = delete_characters(word, &dOneT, counter, &dOneTsize);
    // printf("insert_spaces\n");
    counterAccT = insert_spaces(word, &AccT, counterAccT, &AcctSize, dictionary, hash_table, table_size);

    *result_array = dOneT;
    *acceptedWords = AccT;
    *counterAcc = counterAccT;
    *result_array_size = dOneTsize;
    *acceptedWordsSize = AcctSize;
    return counter;
}

int pre_check(char * word, char * dictionary[], Word ** hash_table, int table_size)
{
    char ** dOne = malloc(sizeof(char *) * 100);
    char ** dTwo = malloc(sizeof(char *) * 100);
    char ** dThree = malloc(sizeof(char *) * 100);
    char ** acceptedWords = malloc(sizeof(char *) * 100);
    int acceptedWordsSize = 100, dOneSize = 100, dTwoSize = 100, dThreeSize = 100, counterAcc = 100;


    int dOneCounter = apply_rules(0, word, dictionary, hash_table, table_size, &dOne, &dOneSize, &acceptedWords, &acceptedWordsSize, &counterAcc);
    printf("Counter %d\n", dOneCounter);
    // for(int i = 0; i < dOneCounter; i++){
    //     if(find_word(dOne[i], dictionary, hash_table, table_size)){
    //         printf("%s\n", dOne[i]);
    //     }
    // }
    for(int i = 0; i < dOneCounter; i++){
        if(find_word(dOne[i], dictionary, hash_table, table_size)){
            // printf("%s\n", dOne[i]);
        }
    }
    int counter2 = 0;
    for(int i = 0; i < dOneCounter; i++){
        counter2 = apply_rules(counter2, dOne[i], dictionary, hash_table, table_size, &dTwo, &dTwoSize, &acceptedWords, &acceptedWordsSize, &counterAcc);
    }
    printf("counter 2 %d\n", counter2);
    // int counter3 = 0;
    // for(int i = 0; i < counter2; i++){
    //     counter3 = apply_rules(counter3, dTwo[i], dictionary, hash_table, table_size, &dThree, &dThreeSize, &acceptedWords, &acceptedWordsSize, &counterAcc);
    // }
    // printf("counter 3 %d\n", counter3);
    // for(int i = 0; i < counter3; i++){
    //     if(find_word(dThree[i], dictionary, hash_table, table_size)){
    //         // printf("%s\n", dThree[i]);
    //     }
    // }

}

int main()
{
    char * dictionary[MAX_LEN];
    int table_size = 0;
    int counter = readfile("diccionario2.txt", dictionary);
    Word ** hash_table = hash_words(dictionary, counter, &table_size);
    // for(int i = 0; i < table_size; i++){
    //     if(hash_table[i] != NULL){
    //         Word * aux = hash_table[i];
    //         while(aux != NULL){
    //             printf("%d ", aux->index);
    //             aux = aux->next;
    //         }
    //         printf("\n");
    //     }else{
    //         printf("NULL\n");
    //     }
    // }
    // find_word("hola\0", dictionary, hash_table, table_size);
    char ** result = malloc(sizeof(char *) * 100);
    pre_check("aaaaaaaaaaaaasiudaaaaa\0", dictionary, hash_table, table_size);
    return 0;
}