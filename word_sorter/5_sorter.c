#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*  This programme filters out words that do not have 5 letters */

int main(int argc, char* argv[])
{
    FILE* dict = NULL;
    char* word = NULL;
    size_t buf_len;
    ssize_t word_len;
    int word_count;


    if (argc != 2){
        fprintf(stderr, "please enter 5_sorter and the filename of the list to be sprted\n");
        exit(0);
    }

    dict = fopen(argv[1], "r");
    if (dict == NULL){
        fprintf(stderr, "could not open %s", argv[1]);
        exit(0);
    }

    while((word_len = getline(&word, &buf_len, dict)) != -1){
        if(word_len == 6){
            fprintf(stdout, "%s", word);
            word_count++;
        }
    }

    fclose(dict);

    //printf("finsihed writing %d wods\n", word_count);

    return 0;
}