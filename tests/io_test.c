#include "../headers/helpers.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
#include "../headers/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_readfile(){
    char ** dictionary = malloc(sizeof(char*) * INITIAL_LEN);
    int dicSize = readfile("./tests/diccionario.txt", &dictionary);
    assert(strcmp(dictionary[0], "aaronica\0") == 0);
    for(int i = 0; i< dicSize; i++){
        free(dictionary[i]);
    }
    free(dictionary);
}
void test_read_suggestion(){
    int tableSize = 0;
    char ** dictionary = malloc(sizeof(char*) * INITIAL_LEN);
    int dicSize = readfile("./tests/diccionario.txt", &dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    assert(read_suggestion(hashTable, dictionary, dicSize, "./tests/suggestion.txt", tableSize) == 3);
    free_all(dictionary, hashTable, tableSize, dicSize);
}

int main(){
    test_readfile();
    test_read_suggestion();
    printf("IO test passed\n");
}
