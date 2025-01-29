#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* This programme sorts words according to their scores in three fields. These fields are given in order of priority below:
    -Highest number of indiviual letters
    -Highest number of individual vowels
    -Lowest scrabble score
*/

// structure that stores a word and 3 measures of how good it is as a guess in order of importance
struct word_score{
    char word[8];
    unsigned short int letters;     // number of individual letters
    unsigned short int vowels;      // number of individual vowels
    unsigned short int scrabble;    // scrable score of the word without any special tiles
};

int score_words(struct word_score** scored_words);  // creates array of words with relevant scores from stdin

int main()
{
    char** pref_words;   
    int i, j, k, l, word_count;
    struct word_score* scored_words = NULL; // array to score all words before they are sorted

    word_count = score_words(&scored_words);

    pref_words = malloc(word_count * 8 * sizeof(char));
    if(pref_words == NULL){
        fprintf(stderr, "failed to allocate memory for pref_words\n");
        exit(0);
    }
    
   // should put in an actual sorting algorithim
    for(i=7; i>=0; i-=1){
        for(j=6; j>=0; j--){
            for(k=0; k<=60; k++){
                for(l=0; l<word_count; l++){
                    if(scored_words[l].letters==i && scored_words[l].vowels==j && scored_words[l].scrabble==k){
                        fprintf(stdout, "%s %d, %d, %d, %d \n",scored_words[l].word, i, j, k, l);   // could store scores somewhere but opted for clean output
                    }
                }
            }
        }
    }

    free(scored_words);
    
    printf("%d\n", word_count);

    return 0;
}

int score_words(struct word_score** scored_words)
{
    size_t buf_len;
    int word_count=0, i, j, score;
    //ssize_t word_len;
    char* word;  
    char letter;

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char vowels[] = "aeiou";

    while(getline(&word, &buf_len, stdin) != -1){
        word_count++;
        //printf("word:%s", word);

        *scored_words = realloc(*scored_words, (word_count+2) * sizeof(struct word_score));
        if(scored_words == NULL){
            fprintf(stderr, "failed to allocate memory to scored_words\n");
            exit(0);
        }

        //printf("allocated memory\n");

        strcpy( ((*scored_words)[word_count-1]).word, word);

        //printf("assigned word\n");

        for(i=0; i<26; i++){
            letter = alphabet[i];
            for(j=0; j<5; j++){
                if(word[j] == letter){
                    ((*scored_words)[word_count-1]).letters++;
                    break;
                }
            }
        }

        //printf("completed letter count\n");

        for(i=0; i<5; i++){
            letter = vowels[i];
            for(j=0; j<5; j++){
                if(word[j] == letter){
                    ((*scored_words)[word_count-1]).vowels++;
                    break;
                }
            }
        }

        score = 0;
        for(i=0; i<5; i++){
            letter = word[i];
            switch (letter) {
                case 'e':
                case 'a':
                case 'i':
                case 'o':
                case 'n':
                case 'r':
                case 't':
                case 'l':
                case 's':
                case 'u':
                    score += 1;
                    break;
                case 'd':
                case 'g':
                    score += 2;
                    break;
                case 'b':
                case 'c':
                case 'm':
                case 'p':
                    score += 3;
                    break;
                case 'f':
                case 'h':
                case 'v':
                case 'w':
                case 'y':
                    score += 4;
                    break;
                case 'k':
                    score += 5;
                    break;
                case 'j':
                case 'x':
                    score += 8;
                    break;
                case 'q':
                case 'z':
                    score += 10;
                    break;
                /*default:
                    fprintf(stderr,"please ensure word contains only lower case letters.\nThe word %s contains the %c character.\n",
                    word, letter);*/
            }
        }
        
        ((*scored_words)[word_count-1]).scrabble = score;
    }

    return(word_count);
}
