#include "wordle.h"

char* check_word(struct guess_information* input)  // checks if a word is a possible guess
{
   bool (*checks[])(char*, char*, char*) = {&check_greens, &check_blacks, &check_yellows};	// functions that do 3 types of check
   for(int i=0; i<NUM_CHECKS; i++){
       if (!check_condition(checks[i], input->word, input->feedback, input->guesses, input->guess_num)){
           return NULL;	// return NULL if the check determines the word is not the guess
       }
   }

   return input->word; // if not elimated by any checks, is a valid guess so make it as guess
}

bool check_condition(bool(func)(char*, char*, char*), char* word, char feedback[MAX_GUESSES+1][WORD_LEN+1], char** guesses, unsigned short int num_guesses) // runs condition func for feedback on each previous guess seperately to check if the word is valid
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
    unsigned short int i;

    for(i=0; i<WORD_LEN; i++){
        if (feedback[i] == 'g' && old_guess[i] != word[i]){
	    return false;
	}	    
    }
    return true;
}

bool check_blacks(char *word, char feedback[WORD_LEN+1], char* old_guess) // checks if a word is valid from the blacks in a previous guess
{
    bool yellow_repeat_flag = false;
    unsigned short int i, j;

    for(i=0; i<WORD_LEN; i++){
        if (feedback[i] != 'b') continue;
	
	for (j=0; j<WORD_LEN; j++){	// check if there's another occurance of the letter marked as black that is marked yellow
	    if (old_guess[i]==old_guess[j] && i!=j && feedback[j]=='y'){
		if (old_guess[i] == word[i]){
		    return false;
		}
		else{
		    yellow_repeat_flag = true;	  	      
		}
	    }
	}
	
	if(yellow_repeat_flag) break;
        for (j=0; j<WORD_LEN; j++){	// if the letter marked balck appears in word (not a repeat) then not a valid guess
            if(old_guess[j]==word[j] && feedback[j]=='g') continue;
            if (word[j] ==old_guess[i]){
		return false;
	    }   	
        }
    }
    return true;
}

bool check_yellows(char *word, char feedback[WORD_LEN+1], char* old_guess)    // checks if a word is valid from the yellows in a previous guess
{

    unsigned short int i, j;

    for(i=0; i<WORD_LEN; i++){
        if (feedback[i] != 'y') continue;
        if (old_guess[i]==word[i]) { // if the yellow letter is guessed in the same place, not a valid guess
		return false;
	}
        for(j=0; j<WORD_LEN; j++){	// iterate through word and see if yellow letter is included
            if (old_guess[i]==word[j]) break;
        }
        if (j==WORD_LEN){	// if yellow letter is not included, not a valid guess
		return false;
	}
    }
    return true;
}
