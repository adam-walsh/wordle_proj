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
           printf("programme failed 1 :(\n");
           break;
        } 

        words_remaining = total_words - ((long) guesses[guess_num] - (long) word_list[0])/word_mem_length;
        printf("guess #%d: %s\n", guess_num+1, guesses[guess_num]);
    }

    return 0;
}

unsigned int read_list(char list[MAX_LIST_LEN][WORD_LEN+2])
{
    FILE* fptr;
    char* word=NULL;
    size_t buf_len;
    unsigned int i;

    fptr = fopen(FILENAME, "r");
    if(fptr == NULL){
        fprintf(stderr, "error in opening word list file");
    }

    for(i=0;(getline(&word, &buf_len, fptr)!= -1) && i<MAX_LIST_LEN; i++){   // should put in some error checking on getline
       safe_copy(list[i], word);
    }

    fclose(fptr);

    return(i);

}

bool get_feedback(char* feedback){
    size_t buf_len=64;
    unsigned short int i;
    char letter;
    char* raw_word = NULL;
    
    while(1){
        if(getline(&raw_word, &buf_len, stdin)!=6){
            printf("please enter exactly 5 characters\n");
            continue;
        }
        else{
            if(safe_copy(feedback, raw_word) == -1){
                continue;
            }
        }
        if(!(strcmp(feedback, "ggggg"))){
            free(raw_word);
            printf("Comlete :)\n");
            return true;
        }
        for(i=0; i<5; i++){
            letter = feedback[i];
            if(letter!='g' && letter!='y' && letter != 'b'){
                printf("please only enter g for green, y for yellow or b for black(grey)\n ");
                break;
            }
        }
        if(i==5){
            free(raw_word);
            return false;
        }
    }
}


char* make_guess(char* prev_guess, char feedback[MAX_GUESSES+1][WORD_LEN+1], char** guesses, long words_remaining, int guess_num, long word_mem_length)
{
    pthread_t threads[NUM_THREADS];
    void *results[NUM_THREADS];
    unsigned short int i, error_check;
    bool complete = false;
    char* guess = NULL;

    struct guess_information guess_input;
    
    for(i=0; i<guess_num; i++){
        safe_copy(guess_input.feedback[i], feedback[i]);
    }
    
    guess_input.guesses = guesses;
    guess_input.guess_num = guess_num;   

    while(!complete && words_remaining > 0){  
        for (i = 0; i < NUM_THREADS; i++) {
            prev_guess += word_mem_length;
            words_remaining-=1;
            guess_input.word = prev_guess;
            error_check = pthread_create(&threads[i], NULL, (void *)&check_word, (void *)&guess_input);
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

/*
char* check_word(struct guess_information* input)   // will replace with actual check
{
    if (!strcmp((*input).word, "wench\n")){
        return (*input).word;
    }
    else{
        return NULL;
        }
}
*/


