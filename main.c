#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include "headers/io.h"
#include "headers/helpers.h"
#include "headers/checker.h"
#include "headers/hashing.h"



int main(int argc, char *argv[])
{
    char * dictionary[MAX_LEN];

    int tableSize = 0;
    
    int dicSize = readfile(argv[1], dictionary);
    
    Word ** hashTable = hash_words(dictionary, dicSize, &tableSize);
    
    read_suggestion(hashTable, dictionary, dicSize, argv[2], tableSize);

    free_all(dictionary, hashTable, tableSize, dicSize);
    
    return 0;
}