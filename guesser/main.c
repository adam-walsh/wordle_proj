#include "wordle.h"

int main()
{
    char word_list[MAX_LIST_LEN][WORD_LEN+2], feedback[MAX_GUESSES+1][WORD_LEN+1];	// sorted list of possible guesses
    char* guesses[MAX_GUESSES+1];	// list of guesses made
    unsigned short int guess_num, word_mem_length;	// guess number, length of memory used by a word in the list
    long words_remaining, total_words;
    bool complete = false;

    total_words = read_list(word_list);
    words_remaining = total_words;
    word_mem_length = (long) word_list[1] - (long)word_list[0];
    guesses[0] = word_list[0];	// make the first guess the first word in the list

    printf("guess #%d: %s\n", 1, guesses[0]);

    for(guess_num = 1; guess_num < MAX_GUESSES && !complete; guess_num++){
        complete = get_feedback(feedback[guess_num-1]);	// check which words are right
        if(complete) break;
        guesses[guess_num] = make_guess(feedback, guesses, words_remaining, guess_num, word_mem_length);
        
        if (guesses[guess_num]==NULL){ // if there is not another word to guess
           printf("programme failed :(\n");
           break;
        } 

        words_remaining = total_words - ((long) guesses[guess_num] - (long) word_list[0])/word_mem_length;
        printf("guess #%d: %s\n", guess_num+1, guesses[guess_num]);
    }

    return 0;
}

