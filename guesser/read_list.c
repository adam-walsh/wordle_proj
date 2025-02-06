#include "wordle.h"

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
