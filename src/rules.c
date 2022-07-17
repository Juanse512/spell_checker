#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "../headers/io.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
void switch_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash){
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
            if(find_word(wordRule, dictionary, hash_table, table_size, 0)){
                insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
            }
        }else{
            apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize, repeatedHash);         
        }
        
        free(wordRule);
    }
    return;
}

//rules
void insert_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash){
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i <= len; i++){
        for(char j = 97; j < 123; j++){
            wordRule = malloc(sizeof(char) * (len + 3));

            memcpy(wordRule, word, (len - (len - i)) + 1);
            memcpy(wordRule + (i + 1), word + i, (len - i) + 1);
            
            wordRule[i] = j;
            if(counter == 0){
                if(find_word(wordRule, dictionary, hash_table, table_size, 0)){
                    insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                }
            }else{
                apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize, repeatedHash);
            }
            free(wordRule);
        }

    }
    return;
}

//rules
void change_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash){
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i < len; i++){
        for(char j = 97; j < 123; j++){
            // printf("%d\n", counter);
            wordRule = malloc(sizeof(char) * (len + 2));
            memcpy(wordRule, word, len + 1);
            wordRule[i] = j;
            if(counter == 0){
                if(find_word(wordRule, dictionary, hash_table, table_size, 0)){
                    insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
                }
            }else{
                apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize, repeatedHash);
            }
            free(wordRule);
        }

    }
    return;
}


//rules
void delete_characters(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size, Word ** repeatedHash){
    int len = strlen(word);
    char * wordRule;
    for(int i = 0; i < len; i++){
        wordRule = malloc(sizeof(char) * (len + 2));
        
        memcpy(wordRule, word, (len - (len - i)) + 1);
        memcpy(wordRule + i, word + (i + 1), (len - i) + 1);

        if(counter == 0){
            if(find_word(wordRule, dictionary, hash_table, table_size, 0)){
                insert_word_result(wordRule, acceptedWords, acceptedWordsSize);
            }
        }else{
            apply_rules(counter - 1, wordRule, dictionary, hash_table, table_size, acceptedWords, acceptedWordsSize, repeatedHash);
        }
        free(wordRule);
    }
    return;
}

//rules
void insert_spaces(char * word, Word * acceptedWords[], int * acceptedWordsSize, int counter, char * dictionary[], Word ** hash_table, int table_size){
    int len = strlen(word);
    for(int i = 0; i < len; i++){
        char * firstWord = malloc(sizeof(char) * ((len - (len - i)) + 2));
        char * secondWord = malloc(sizeof(char) * ((len - i) + 2));

        memcpy(firstWord, word, (len - (len - i)) + 1);
        firstWord[(len - (len - i))] = '\0';
        memcpy(secondWord, word + i, (len - i) + 1);
        secondWord[(len - i)] = '\0';
        
        
        if(find_word(firstWord, dictionary, hash_table, table_size, 0) && find_word(secondWord, dictionary, hash_table, table_size, 0)){
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

//rules
int apply_rules(int counter, char * word, char * dictionary[], Word ** hash_table, int table_size, Word * acceptedWords[], int * acceptedWordsSize, Word ** repeatedHash){
    if(*acceptedWordsSize >= 5) return 0;
    unsigned int hash = hash_first(word);
    unsigned int position = hash % MAX_LEN_2;
    if(find_word(word, dictionary, repeatedHash, MAX_LEN_2, counter)){
        return 0;
    }else{
        char * newWord = malloc(sizeof(char) * (strlen(word) + 1));
        memcpy(newWord, word, strlen(word) + 1);
        repeatedHash[position] = insert_word(counter,repeatedHash[position], hash, newWord);
    }
    insert_spaces(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size);
    delete_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size, repeatedHash);
    switch_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size, repeatedHash);
    change_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size, repeatedHash);
    insert_characters(word, acceptedWords, acceptedWordsSize, counter, dictionary, hash_table, table_size, repeatedHash);
    return counter;
}