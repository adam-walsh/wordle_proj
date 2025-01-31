play_wordle: main.o check_word.o process_word.o
	gcc -o play_wordle main.o check_word.o process_word.o -Wall

main.o: main.c wordle.h
	gcc -o main.o -c main.c -Wall

check_word.o: check_word.c wordle.h
	gcc -o check_word.o -c check_word.c -Wall

process_word.o: process_word.c wordle.h
	gcc -o process_word.o -c process_word.c -Wall

