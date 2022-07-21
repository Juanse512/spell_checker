#include "../headers/helpers.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
#include "../headers/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_murmur_hash(){
    unsigned int hash = MurmurHash2("hola\0", strlen("hola\0"), 13);
    assert(hash == 3577387992);
}

void test_hash_first(){
    unsigned int hash = hash_first("hola\0");
    assert(hash == 3577387992);
}

void test_hash_words_find_words(){
    int counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("diccionario.txt", dictionary);
    Word ** hash_table = hash_words(dictionary, dicSize, &counter);
    assert(find_word("hola\0", dictionary, hash_table, counter, 0));
    free_all(dictionary, hash_table, counter, dicSize);
    // assert(hash == 3577387992);
}

int main(){
    test_murmur_hash();
    test_hash_first();
    test_hash_words_find_words();
}
