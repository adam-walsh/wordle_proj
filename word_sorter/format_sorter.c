#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This programme filters out word with special characters*/

int main()
{
    size_t buf_len, i, valid;
    char* word;
    while(getline(&word, &buf_len, stdin) != -1){
        valid=1;
        for(i=0; i<5; i++){
            if(word[i]<97 || word[i]>122){
                valid=0;
                break;
            }
        }

        if(valid==1){
            word[5] = '\0';
            fprintf(stdout, "%s\n", word);
        }
    }

    return 0;
}