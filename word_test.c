#include "wordle.h"

int main()
{
    char* word_to_check = ['b', 'a', 'l', 'l', 's'];
    char** feedback = [['g', 'b', 'b', 'b', 'b']];
    char** guesses = [['i', 'r', 'a', 't', 'e']];
    
    guess_num = 1;
    for(int i=0; i<guess_num+1; i++){
        safe_copy(guess_input.feedback[i], feedback[i]);
    }
    
    guess_input.guesses = guesses;
    guess_input.guess_num = guess_num;   


    return 0;
}
