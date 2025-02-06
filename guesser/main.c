#include "wordle.h"

int main()
{
    char word_list[MAX_LIST_LEN][WORD_LEN+2], feedback[MAX_GUESSES+1][WORD_LEN+1];
    char* guesses[MAX_GUESSES+1];
    char* prev_guess = word_list[0];
    unsigned short int guess_num;
    long words_remaining, word_mem_length, total_words;
    bool complete = false;

    total_words = read_list(word_list);
    words_remaining = total_words;
    word_mem_length = (long) word_list[1] - (long)word_list[0];
    guesses[0] = word_list[0];

    printf("guess #%d: %s\n", 1, guesses[0]);

    for(guess_num = 1; guess_num < MAX_GUESSES && !complete; guess_num++){
        complete = get_feedback(feedback[guess_num-1]);
        prev_guess = guesses[guess_num-1];
        if(complete==true){
            break;
        }
        guesses[guess_num] = make_guess(prev_guess, feedback, guesses, words_remaining, guess_num, word_mem_length);
        
        if (guesses[guess_num]==NULL){
           printf("programme failed :(\n");
           break;
        } 

        words_remaining = total_words - ((long) guesses[guess_num] - (long) word_list[0])/word_mem_length;
        printf("guess #%d: %s\n", guess_num+1, guesses[guess_num]);
    }

    return 0;
}

