play_wordle: main.o check_word.o process_word.o read_list.o get_feedback.o make_guess.o 
	gcc -o play_wordle main.o check_word.o process_word.o read_list.o get_feedback.o make_guess.o -Wall

main.o: main.c wordle.h
	gcc -o main.o -c main.c -Wall

check_word.o: check_word.c wordle.h
	gcc -o check_word.o -c check_word.c -Wall

process_word.o: process_word.c wordle.h
	gcc -o process_word.o -c process_word.c -Wall

read_list.o: read_list.c wordle.h
	gcc -o read_list.o -c read_list.c -Wall

get_feedback.o: get_feedback.c wordle.h
	gcc -o get_feedback.o -c get_feedback.c -Wall

make_guess.o: make_guess.c wordle.h
	gcc -o make_guess.o -c make_guess.c -Wall

