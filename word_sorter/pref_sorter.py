def count_occurances(word, check_list):
    occurances = 0
    for letter in check_list:
        if letter in word:
            occurances = occurances + 1
    return occurances

def find_scrabble_score(word):
    score = 0
    score_matrix = ["aeiounrtlsdg", "bcmp", "fhvwy", "k", "jx", "qz"]

    for i in word:
        for j in range(len(score_matrix)):
            if i in score_matrix[j]:
                score = score + j
    return score

class score:
    def __init__(self, word):
        alphabet = "abcdefghijklmnopqrstuvwxyz"
        vowels = "aeiou"

        letters = count_occurances(word, alphabet)
        vowels = count_occurances(word, vowels)
        scrabble_score = find_scrabble_score(word)
        
        self.score = [letters, vowels, scrabble_score]
        self.word = word

max_letters = 5
max_vowels = 4
max_scrabble_score = 20

scored_words = []

while True:
    try:
        word = input()
    except EOFError:
        break
    
    scored_word = score(word)
    scored_words.append(scored_word)

sorted_words = sorted(scored_words, key=lambda x: (-x.score[0], -x.score[1], x.score[2]))

for i in sorted_words:
    print(i.word)
