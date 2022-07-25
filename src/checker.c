#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "../headers/helpers.h"
#include "../headers/io.h"
#include "../headers/hashing.h"
#include "../headers/rules.h"
void insert_word_result(char * word, Word ** acceptedWords, int * acceptedWordsSize){
    if(*acceptedWordsSize >= 5) return;
    
    int flag = 0;
    unsigned int wordHash = hash_first(word);
    
    for(int i = 0; i < *acceptedWordsSize; i++){
        if(acceptedWords[i] != NULL){
            //Si la palabra ya se encuentra en el array no la guardo
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

void pre_check(char * word, char * dictionary[], Word ** hashTable, int tableSize, Word ** acceptedWords, int * acceptedWordsCounter){
    
    int distance = 0;
    Word * repeatedHash[MAX_LEN];
    clean_array(repeatedHash, MAX_LEN);
    
    while(distance < 3 && *acceptedWordsCounter < 5){
        apply_rules(distance, word, dictionary, hashTable, tableSize, acceptedWords, acceptedWordsCounter, repeatedHash);
        distance++;
    }
    
    for(int i = 0; i < MAX_LEN; i++){
        free_list(repeatedHash[i]);
    }
    
    return;
}

Word ** suggest_word(char * word, char * dictionary[], int dicSize, Word ** hashTable, int tableSize, int * acceptedWordsCounter){
    *acceptedWordsCounter = 0;
   
    Word ** acceptedWords = malloc(sizeof(Word *) * 6);
   
    clean_array(acceptedWords, 6);
    pre_check(word, dictionary, hashTable, tableSize, acceptedWords, acceptedWordsCounter);
 
    return acceptedWords;
}

void check_word(char * word, char * dictionary[], Word** hashTable, int tableSize, int dicSize, int line, char * outPath, Word ** calculatedWords){
    Word ** acceptedWords;
    
    int acceptedWordsCounter = 0;
    
    unsigned int hash = 0, position = 0;
    
    FILE *out;
    out = fopen(outPath, "a+");
    if (out == NULL)
        quit("Archivo de salida no especificado");
    //Si la palabra no es valida ni la calculamos antes
    if(!find_word(word, dictionary, hashTable, tableSize, 0) && !find_word(word, dictionary, calculatedWords, tableSize, 0)){
        
        hash = hash_first(word);
        position = hash % tableSize;
        
        calculatedWords[position] = insert_word(0, calculatedWords[position], hash, word);
        //Insertamos la palabra e imprimimos las sugerencias
        
        fprintf(out, "Palabra %s en la linea %d es erronea, sugerencias:\n", word, line);
        
        acceptedWords = suggest_word(word, dictionary, dicSize, hashTable, tableSize, &acceptedWordsCounter);
        
        for(int i = 0; i < acceptedWordsCounter; i++){
            fprintf(out, "%s\n", acceptedWords[i]->word);
        }
        
        free_accepted(acceptedWords);
    }else{
        free(word);
    }
    fclose(out);
}





