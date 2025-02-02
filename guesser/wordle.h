#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_LIST_LEN 20000
#define FILENAME "../word_sorter/list.txt"
#define NUM_THREADS 4 
#define MAX_GUESSES 20
#define INVALID_CHARACTER 33
#define WORD_LEN 6

struct guess_information {
    char* word;
    char feedback[MAX_GUESSES+1][WORD_LEN+1];
    char** guesses;
    int guess_num;
};

// functions in main file
unsigned int read_list(char list[MAX_LIST_LEN][WORD_LEN+2]);        // reads in a list of words form a file and stores it in the list variable
bool get_feedback(char* feedback);  // gets feedback on the user for a guess
char* make_guess(char* prev_guess, char feedback[MAX_GUESSES+1][WORD_LEN+1], char** guesses, long word_index, int guess_num, long word_mem_length); // moves pointer along array to next guess not ruled out
void trim_newline(char* string); // removes the newline character at the end of a string
                                
// functions in check_word file
char* check_word(struct guess_information* input);  // checks if a word is a possible guess
bool check_condition(bool(func)(char*, char*, char*), char* word, char feedback[MAX_GUESSES+1][WORD_LEN+1], char** guesses, unsigned short int num_guesses); // runs condition func for all feedback to check if the word is valid
bool check_greens(char* word, char feedback[WORD_LEN+1], char* old_guess); // checks if a word is valid from the greens in a previous guess
bool check_blacks(char *word, char feedback[WORD_LEN+1], char* old_guess); // checks if a word is valid from the blacks in a previous guess
bool check_yellows(char *word, char feedback[WORD_LEN+1], char* old_guess);    // checks if a word is valid from the yellows in a previous guess
bool check_if_second_occurance(char* word, unsigned short int letter_index);    // checks if a letter has already occured in a word

// functions in process_word
int safe_copy(char *new_address, char *word); // copies a word in a safe way
char filter_character(char letter); // returns a lowercase letter

#endif
