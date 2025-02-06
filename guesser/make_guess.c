#include "wordle.h"

char* make_guess(char* prev_guess, char feedback[MAX_GUESSES+1][WORD_LEN+1], char** guesses, long words_remaining, int guess_num, long word_mem_length)
{
    pthread_t threads[NUM_THREADS];
    void *results[NUM_THREADS];
    unsigned short int i, j, error_check;
    bool complete = false;
    char* guess = NULL;
    struct guess_information guess_input[NUM_THREADS];
    
    for(i=0; i<NUM_THREADS; i++){  
    	guess_input[i].guesses = guesses;
    	guess_input[i].guess_num = guess_num;
 	for(j=0; j<guess_num; j++){
        	safe_copy(guess_input[i].feedback[j], feedback[j]);
    	}
   }	

    while(!complete && words_remaining > 0){  
        for (i = 0; i < NUM_THREADS; i++) {
            prev_guess += word_mem_length;
            words_remaining-=1;
            guess_input[i].word = prev_guess;
            error_check = pthread_create(&threads[i], NULL, (void *)&check_word, (void *)&guess_input[i]);
            if (error_check) {
                perror("pthread_create");
                exit(1);
            }
        }
        for (i = 0; i < NUM_THREADS; i++) {
            if (pthread_join(threads[i], &results[i]) != 0) {
                perror("pthread_join");
                exit(1);
            }

            if((char*)results[i]!=NULL && !complete){
                complete = true;
                guess = (char*)results[i];
	    }
        }
    }

    if (words_remaining <= 0){
        return NULL;
    }

    return guess;
}
