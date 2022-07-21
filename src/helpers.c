#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "../headers/io.h"

char * parse_word(char * word){
    char * parsedWord = malloc(sizeof(char) * strlen(word) + 2);
    int counter = 0; 
    for(int i = 0; i < strlen(word); i++){
        if(isalpha(word[i])){
            parsedWord[counter++] = tolower(word[i]);
        }
    }
    parsedWord[counter] = '\0';
    return parsedWord;
}

void free_accepted(Word ** acceptedWords){   
    for(int i = 0; i < 6; i++){
        if(acceptedWords[i] != NULL){
            free(acceptedWords[i]->word);
            free(acceptedWords[i]);
        }
    }
    free(acceptedWords);
}

void free_all(char * dictionary[], Word ** hashTable, int tableSize, int dicSize){   
    for(int i = 0; i < dicSize; i++){
        free(dictionary[i]);
    }
    for(int i = 0; i < tableSize; i++){
        free_list(hashTable[i]);
    }
    free(hashTable);
}

void free_list(Word * word){
    if(word == NULL)
        return;
    if(word->word != NULL) free(word->word);
    Word * next = word->next;
    free(word);
    free_list(next);
}

int check_len(char ** array[], int counter, int arraySize){
    int newSize = arraySize;
    if(arraySize <= counter){
        newSize = (newSize * 3);
        // printf("IN HERE %d %d\n", counter, newSize);
        *array = realloc(*array, sizeof(char *) * (newSize));
    }
    return newSize;
}

void save_word(char * word, char * dictionary[], int index){
    dictionary[index] = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(dictionary[index], word);
}

Word * insert_word(int index, Word * word, unsigned int hash, char * wordChar){
    Word * newWord = malloc(sizeof(Word));
    newWord->index = index;
    newWord->next = NULL;
    newWord->hash = hash;
    newWord->word = wordChar;
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

void clean_array(Word ** hashTable, int counter){
    for(int i = 0; i < counter; i++)
    {
        hashTable[i] = NULL;
    }
}