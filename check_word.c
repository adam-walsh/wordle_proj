#include "wordle.h"

char* check_word(struct guess_information* input)  // checks if a word is a possible guess
{
/*
    printf("%s\n", input->word);
    
    for (int i=0; i<guess_num; i++){
        printf("%d: ", i);
        printf("%s,\t", input->guesses[i]);
        printf("%s\n", input->feedback[i]);
    }
    printf("\n");
  */
    /*  
    if(!strcmp(word, "aisle")) {
        return word;
    }
    
    if(!strcmp(word, "aloes")) {
        return word;
    }
 
    if(!strcmp(word, "arose")) {
        return word;
    }
 
    if(!strcmp(word, "irate")) {
        return word;
    }
    
    return NULL;
*/


    if (!check_condition(&check_greens, input->word, input->feedback, input->guesses, input->guess_num)){
        return NULL;
    }
    else if (!check_condition(&check_blacks, input->word, input->feedback, input->guesses, input->guess_num)){
        return NULL;
    }
    else if (!check_condition(&check_yellows, input->word, input->feedback, input->guesses, input->guess_num)){
        return NULL;
    }
    else{
        return input->word;
    }
}

bool check_condition(bool(func)(char*, char*, char*), char* word, char feedback[MAX_GUESSES+1][WORD_LEN+1], char** guesses, unsigned short int num_guesses) // runs condition func for all feedback to check if the word is valid
{
    for (unsigned short int i=0; i<num_guesses; i++){
        if(!func(word, feedback[i], guesses[i])) {
            return false;
        }
    }
    return true;
}

bool check_greens(char* word, char feedback[WORD_LEN+1], char* old_guess) // checks if a word is valid from the greens in a previous guess
{
    for(int i=0; i<WORD_LEN; i++){
        if (feedback[i] == 'g' && old_guess[i] != word[i]) return false;
    }
    return true;
}

bool check_blacks(char *word, char feedback[WORD_LEN+1], char* old_guess) // checks if a word is valid from the blacks in a previous guess
{
    for(int i=0; i<WORD_LEN; i++){
        if (feedback[i] != 'b') continue;
        for (int j=0; j<WORD_LEN; j++){
            if(old_guess[j]==word[j] && feedback[j]=='g') continue;
            if (word[j] ==old_guess[i])return false;
        }
    }
    return true;
}

bool check_yellows(char *word, char feedback[WORD_LEN+1], char* old_guess)    // checks if a word is valid from the yellows in a previous guess
{
    int j;

    for(int i=0; i<WORD_LEN; i++){
        if (feedback[i] != 'y') continue;
        if (old_guess[i]==word[i]) return false;
        for(j=0; j<WORD_LEN; j++){
            if (old_guess[i]==word[j]) break;
        }
        if (j==WORD_LEN) return false;
    }
    return true;
}
/*
char* check_if_second_occurance(char* word, char* letter)    // checks if a letter has already occured in a word
{
    for(int i=0; i,WORD_LEN; i++){
        if(word+i==letter){
            continue;
        }
        if(word[i] == *letter){
            return NULL;
        }
}
*/
