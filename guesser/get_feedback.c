#include "wordle.h"

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
