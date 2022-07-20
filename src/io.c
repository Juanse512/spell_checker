#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "../headers/helpers.h"
#include "../headers/checker.h"

void quit(const char *s)
{
	perror(s);
	exit(1);
}

int readfile(const char *path, char * dictionary[])
{
	char aux[100];
	
    FILE *f = fopen(path, "rb");
	
    int c, i = 0, counter = 0;
	
    if (f == NULL)
        quit("readfile.fopen");
    
    int flag = 1;
	
    while (flag) {
        c = getc(f);
        
        if(c == '\n' || c == EOF){
            aux[i - 1] = '\0';
        
            saveWord(aux, dictionary, counter);
        
            counter++;
        
            i = 0;
        
            if(c == EOF) flag = 0;
        }else{
            aux[i++] = c;
        }
	}
	
    fclose(f);
    
    return counter;
}

void read_suggestion(Word ** hashTable, char * dictionary[], int dicSize, char * path, int tableSize)
{
    char aux[100];
	char * parsedWord;

    FILE *f = fopen(path, "rb");
	
    int c, i = 0, counter = 0;
	
    if (f == NULL)
        quit("readfile.fopen");
    
    int flag = 1;
	int line = 1;
    while (flag) {
        c = getc(f);
        if(c == '\n' || c == EOF || c == ' '){
            aux[i] = '\0';
            parsedWord = parse_word(aux);
            check_word(parsedWord, dictionary, hashTable, tableSize, dicSize, line);
            free(parsedWord);
            counter++;
        
            i = 0;
            if(c == '\n') line++;
            if(c == EOF) flag = 0;
        }else{
            aux[i++] = c;
        }
	}
    fclose(f);
}