all: spell_check
spell_check: main.c ./src/checker.c ./src/hashing.c ./src/helpers.c ./src/io.c ./src/rules.c
	- gcc -g -Wall main.c ./src/checker.c ./src/hashing.c ./src/helpers.c ./src/io.c ./src/rules.c -o spell_check -lm 
clean: spell_check
	- rm spell_check