#include "../headers/helpers.h"
#include "../headers/checker.h"
#include "../headers/hashing.h"
#include "../headers/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_clean_array(){
    Word ** accepted = malloc(sizeof(Word *) * 6);
    clean_array(accepted, 6);
    for(int i = 0; i < 6; i++){
        assert(accepted[i] == NULL);
    }
    free(accepted);
}

void test_insert_word(){
    Word * first = malloc(sizeof(Word));
    first->word = malloc(sizeof(char) * 6);
    first->next = NULL;
    strcpy(first->word, "como\0");
    first = insert_word(1, first, hash_first("hola\0"), "hola\0");
    assert(strcmp(first->next->word, "hola\0") == 0);
    assert(first->next->index == 1);
    assert(first->next->hash == 3577387992);
    assert(strcmp(first->word, "como\0") == 0);
    free(first->next);
    free(first->word);
    free(first);
}

void test_save_word(){
    char * dic[10];
    save_word("hola\0", dic, 0);
    assert(strcmp(dic[0], "hola\0") == 0);
    free(dic[0]);
}

void test_check_len(){
    int len = 3, size = 2;
    char *** dic1 = malloc(sizeof(char **));
    char ** dic = malloc(sizeof(char *) * size);
    *dic1 = dic;
    dic1 = check_len(dic1, len, &size);
    assert(size == 6);
    free(*dic1);
    free(dic1);
}

void test_parse_word(){
    char * parsed = parse_word("HoLa.?\0");
    assert(strcmp(parsed, "hola\0") == 0);
    free(parsed);
}

int main(){
    test_clean_array();
    test_insert_word();
    test_save_word();
    test_check_len();
    test_parse_word();
    printf("Helpers test passed\n");
}
