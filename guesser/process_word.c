#include "wordle.h"

int safe_copy(char *new_address, char *word)
{
    char letter;
    for(int i=0; i<WORD_LEN-1; i++){
        letter = word[i];
        letter = filter_character(letter);
        if(letter == INVALID_CHARACTER){
            printf("invalid character at position %d\n the invalid character is %d \n.", i, word[i]);
            return -1;
        }
        new_address[i] = letter;
    }
    new_address[WORD_LEN] = '\0'; 
    return 0;
}

char filter_character(char letter)
{
    if (letter>='a' && letter<='z'){
            return letter;
    }

    if (letter>='A' && letter<='Z'){
            return letter + 32;
    }

    return INVALID_CHARACTER;
    
}
