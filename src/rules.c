#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "../headers/io.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
void switch_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash){
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
            if(find_word(wordRule, dictionary, hashTable, tableSize, 0)){
                insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
            }
        }else{
            apply_rules(counter - 1, wordRule, dictionary, hashTable, tableSize, acceptedWords, acceptedWordsSize, repeatedHash);         
        }
        
        free(wordRule);
    }
    return;
}

void insert_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash){
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i <= len; i++){
        for(char j = 97; j < 123; j++){
            wordRule = malloc(sizeof(char) * (len + 3));

            memcpy(wordRule, word, (len - (len - i)) + 1);
            memcpy(wordRule + (i + 1), word + i, (len - i) + 1);
            
            wordRule[i] = j;
            if(counter == 0){
                if(find_word(wordRule, dictionary, hashTable, tableSize, 0)){
                    insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                }
            }else{
                apply_rules(counter - 1, wordRule, dictionary, hashTable, tableSize, acceptedWords, acceptedWordsSize, repeatedHash);
            }
            free(wordRule);
        }

    }
    return;
}

void change_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash){
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i < len; i++){
        for(char j = 97; j < 123; j++){
            wordRule = malloc(sizeof(char) * (len + 2));
            memcpy(wordRule, word, len + 1);
            wordRule[i] = j;
            if(counter == 0){
                if(find_word(wordRule, dictionary, hashTable, tableSize, 0)){
                    insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                }
            }else{
                apply_rules(counter - 1, wordRule, dictionary, hashTable, tableSize, acceptedWords, acceptedWordsSize, repeatedHash);
            }
            free(wordRule);
        }

    }
    return;
}


void delete_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize, Word ** repeatedHash){
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i < len; i++){
        wordRule = malloc(sizeof(char) * (len + 2));
        
        memcpy(wordRule, word, (len - (len - i)) + 1);
        memcpy(wordRule + i, word + (i + 1), (len - i) + 1);

        if(counter == 0){
            if(find_word(wordRule, dictionary, hashTable, tableSize, 0)){
                insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
            }
        }else{
            apply_rules(counter - 1, wordRule, dictionary, hashTable, tableSize, acceptedWords, acceptedWordsSize, repeatedHash);
        }
        free(wordRule);
    }
    return;
}

void insert_spaces(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hashTable, int tableSize){
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        char * firstWord = malloc(sizeof(char) * ((len - (len - i)) + 2));
        char * secondWord = malloc(sizeof(char) * ((len - i) + 2));

        memcpy(firstWord, word, (len - (len - i)) + 1);
        firstWord[(len - (len - i))] = '\0';
        memcpy(secondWord, word + i, (len - i) + 1);
        secondWord[(len - i)] = '\0';
        
        
        if(find_word(firstWord, dictionary, hashTable, tableSize, 0) && find_word(secondWord, dictionary, hashTable, tableSize, 0)){
            firstWord[(len - (len - i))] = ' ';
            firstWord[(len - (len - i)) + 1] = '\0';
            char * newWord = malloc(sizeof(char) * (len + 2));
            memcpy(newWord, firstWord, strlen(firstWord) + 1);
            memcpy(newWord + strlen(newWord), secondWord, strlen(secondWord) + 1);
            insert_word_result(newWord, acceptedWords, acceptedWordsSize);
            free(newWord);
        }
        free(firstWord);
        free(secondWord);

        
    }
    return;
}

int apply_rules(int counter, char * word, char * dictionary[], Word ** hashTable, int tableSize, Word * acceptedWords[], int * acceptedWordsSize, Word ** repeatedHash){
    if(*acceptedWordsSize >= 5) return 0;
    unsigned int hash = hash_first(word);
    unsigned int position = hash % MAX_LEN_2;
    //Si la palabra ya se encuentra retorno, si no la guardo y luego calculo
    if(find_word(word, dictionary, repeatedHash, MAX_LEN_2, counter)){
        return 0;
    }else{
        char * newWord = malloc(sizeof(char) * (strlen(word) + 1));
        memcpy(newWord, word, strlen(word) + 1);
        repeatedHash[position] = insert_word(counter,repeatedHash[position], hash, newWord);
    }
    insert_spaces(word, acceptedWords, acceptedWordsSize, counter, dictionary, hashTable, tableSize);
    delete_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hashTable, tableSize, repeatedHash);
    switch_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hashTable, tableSize, repeatedHash);
    change_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hashTable, tableSize, repeatedHash);
    insert_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hashTable, tableSize, repeatedHash);
    return counter;
}