#include "../headers/helpers.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
#include "../headers/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_insert_word_result(){
    Word * hash[1000];
    int counter = 1;
    hash[0] = malloc(sizeof(Word));
    hash[0]->word = malloc(sizeof(char) * 5);
    strcpy(hash[0]->word, "hola\0");
    hash[0]->hash = MurmurHash2(hash[0]->word, strlen(hash[0]->word), SEED_HASH);
    insert_word_result("hola\0", hash, &counter);
    insert_word_result("como\0", hash, &counter);
    assert(strcmp(hash[0]->word, "hola\0") == 0);
    assert(strcmp(hash[1]->word, "como\0") == 0);
    free(hash[0]->word);
    free(hash[0]);
    free(hash[1]->word);
    free(hash[1]);
}

void test_pre_check(){
    int counter = 0, tableSize = 0;
    Word ** accepted = malloc(sizeof(Word *) * 6);
    char ** dictionary = malloc(sizeof(char*) * INITIAL_LEN);
    int dicSize = readfile("./tests/diccionario.txt", &dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    pre_check("holx\0", dictionary, hashTable, tableSize, accepted, &counter);
    assert(strcmp(accepted[0]->word, "hola\0") == 0);
    for(int i = 0; i < counter; i++){
        free(accepted[i]->word);
        free(accepted[i]);
    }
    free(accepted);
    free_all(dictionary, hashTable, tableSize, dicSize);
}

void test_suggest_word(){
    int counter = 0, tableSize = 0;
    char ** dictionary = malloc(sizeof(char*) * INITIAL_LEN);
    int dicSize = readfile("diccionario.txt", &dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    Word ** accepted = suggest_word("holx\0",dictionary, dicSize, hashTable, tableSize, &counter);
    assert(strcmp(accepted[0]->word, "hola\0") == 0);
    for(int i = 0; i < counter; i++){
        free(accepted[i]->word);
        free(accepted[i]);
    }
    free(accepted);
    free_all(dictionary, hashTable, tableSize, dicSize);
}

int main(){
    test_insert_word_result();
    test_pre_check();
    test_suggest_word();
    printf("Checker test passed\n");
}
