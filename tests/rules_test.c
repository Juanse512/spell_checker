#include "../headers/helpers.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
#include "../headers/io.h"
#include "../headers/rules.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_switch_characters(){
    Word * repeatedHash[MAX_LEN_2];
    clean_array(repeatedHash, MAX_LEN_2);
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    int tableSize = 0, counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("./tests/diccionario.txt", dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    switch_characters("hloa\0", accepted , &counter, 0, dictionary, hashTable, tableSize, repeatedHash);
    // switch_characters("lhao\0", accepted , &counter, 2, dictionary, hashTable, tableSize, repeatedHash);
    assert(strcmp("hola\0", accepted[0]->word) == 0);
    free_all(dictionary, hashTable, tableSize, dicSize);
    free_accepted(accepted);
}
void test_insert_spaces(){
    Word * repeatedHash[MAX_LEN_2];
    clean_array(repeatedHash, MAX_LEN_2);
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    int tableSize = 0, counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("./tests/diccionario.txt", dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    insert_spaces("holacomo\0", accepted, &counter, 0, dictionary, hashTable, tableSize);
    // switch_characters("lhao\0", accepted , &counter, 2, dictionary, hashTable, tableSize, repeatedHash);
    assert(strcmp("hola como\0", accepted[0]->word) == 0);
    free_all(dictionary, hashTable, tableSize, dicSize);
    free_accepted(accepted);
}
void test_delete_characters(){
    Word * repeatedHash[MAX_LEN_2];
    clean_array(repeatedHash, MAX_LEN_2);
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    int tableSize = 0, counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("./tests/diccionario.txt", dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    delete_characters("holax\0", accepted , &counter, 0, dictionary, hashTable, tableSize, repeatedHash);
    // switch_characters("lhao\0", accepted , &counter, 2, dictionary, hashTable, tableSize, repeatedHash);
    assert(strcmp("hola\0", accepted[0]->word) == 0);
    free_all(dictionary, hashTable, tableSize, dicSize);
    free_accepted(accepted);
}
void test_change_characters(){
    Word * repeatedHash[MAX_LEN_2];
    clean_array(repeatedHash, MAX_LEN_2);
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    int tableSize = 0, counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("./tests/diccionario.txt", dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    change_characters("holx\0", accepted , &counter, 0, dictionary, hashTable, tableSize, repeatedHash);
    // switch_characters("lhao\0", accepted , &counter, 2, dictionary, hashTable, tableSize, repeatedHash);
    assert(strcmp("hola\0", accepted[0]->word) == 0);
    free_all(dictionary, hashTable, tableSize, dicSize);
    free_accepted(accepted);
}
void test_insert_characters(){
    Word * repeatedHash[MAX_LEN_2];
    clean_array(repeatedHash, MAX_LEN_2);
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    int tableSize = 0, counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("./tests/diccionario.txt", dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    insert_characters("hol\0", accepted , &counter, 0, dictionary, hashTable, tableSize, repeatedHash);
    // switch_characters("lhao\0", accepted , &counter, 2, dictionary, hashTable, tableSize, repeatedHash);
    assert(strcmp("hola\0", accepted[0]->word) == 0);
    free_all(dictionary, hashTable, tableSize, dicSize);
    free_accepted(accepted);
}
void test_apply_rules(){
    Word * repeatedHash[MAX_LEN_2];
    clean_array(repeatedHash, MAX_LEN_2);
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    int tableSize = 0, counter = 0;
    char * dictionary[MAX_LEN];
    int dicSize = readfile("./tests/diccionario.txt", dictionary);
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    apply_rules(0, "lhao\0", dictionary, hashTable, tableSize, accepted, &counter, repeatedHash);
    apply_rules(1, "lhao\0", dictionary, hashTable, tableSize, accepted, &counter, repeatedHash);
    apply_rules(2, "lhao\0", dictionary, hashTable, tableSize, accepted, &counter, repeatedHash);
    assert(strcmp("hao\0", accepted[0]->word) == 0);
    assert(strcmp("chao\0", accepted[1]->word) == 0);
    assert(strcmp("ha\0", accepted[2]->word) == 0);
    assert(strcmp("aho\0", accepted[3]->word) == 0);
    assert(strcmp("bao\0", accepted[4]->word) == 0);
    free_all(dictionary, hashTable, tableSize, dicSize);
    free_accepted(accepted);
    for(int i = 0; i < MAX_LEN_2; i++){
        free_list(repeatedHash[i]);
    }
}


int main(){
    test_switch_characters();
    test_insert_spaces();
    test_delete_characters();
    test_change_characters();
    test_insert_characters();
    test_apply_rules();
    printf("Rules test passed\n");
}
