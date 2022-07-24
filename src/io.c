#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../headers/helpers.h"
#include "../headers/checker.h"

void quit(const char *s){
	perror(s);
	exit(1);
}

int readfile(const char *path, char *** dictionaryP){
	char aux[100];
	char ** dictionary = *dictionaryP;
    FILE *f = fopen(path, "rb");
	
    int c, i = 0, counter = 0, size = INITIAL_LEN;
	
    if (f == NULL)
        quit("readfile.fopen");
    
    int flag = 1;
	
    while (flag) {
        c = getc(f);
        
        if(c == '\n' || c == EOF){
            aux[i] = '\0';
            dictionaryP = check_len(dictionaryP, counter, &size);
            dictionary = *dictionaryP;
            // printf("%s\n", aux);
            save_word(aux, dictionary, counter);
        
            counter++;
        
            i = 0;
        
            if(c == EOF) flag = 0;
        }else{
            if(c != 13){
                aux[i++] = c;
            }
        }
	}
	
    fclose(f);
    
    return counter;
}

int read_suggestion(Word ** hashTable, char * dictionary[], int dicSize, char * path, int tableSize, char * outPath){
    char aux[100];
	char * parsedWord;

    FILE *f = fopen(path, "rb");
	
    int c, i = 0, counter = 0;
	
    if (f == NULL)
        quit("readfile.fopen");
    
    int flag = 1;
	int line = 1;

    Word ** repeatedWord = malloc(sizeof(Word *) * tableSize);
    clean_array(repeatedWord, tableSize);

    while (flag) {
        c = getc(f);
        if(c == '\n' || c == EOF || c == ' '){
            aux[i] = '\0';
            parsedWord = parse_word(aux);
            check_word(parsedWord, dictionary, hashTable, tableSize, dicSize, line, outPath, repeatedWord);
            // free(parsedWord);
            counter++;
        
            i = 0;
            if(c == '\n') line++;
            if(c == EOF) flag = 0;
        }else{
            aux[i++] = c;
        }
	}
    
    for(int i = 0; i < tableSize; i++){
        free_list(repeatedWord[i]);
    }
    free(repeatedWord);

    fclose(f);
    return counter;
}