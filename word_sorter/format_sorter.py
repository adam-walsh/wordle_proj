from unidecode import unidecode

while True:
    try:
        input_word = input()
    except EOFError:
        break
    if len(input_word)!=5:
        continue
    input_word = input_word.lower()
    if input_word.isalpha():
        print(unidecode(input_word))
