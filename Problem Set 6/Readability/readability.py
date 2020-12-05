from cs50 import get_string

# Coleman - Liau index = 0.0588 * L - 0.296 * S - 15.8
# L is average # of letters per 100 words
# S is average number of sentences per 100 words

# all print functions are for testing purposes

# get text from user
text = get_string("Text: ")

word_punctuation = [" ", ",", ";"]
sentence_punctuation = [".", "!", "?"]

# split text by spaces to find number of words
words = text.split(" ")
print(words)

word_count = len(words)

sentence_count = 0

letter_count = 0

for i in text:
    # use isalpha() method to find all letters
    if i.isalpha():
        letter_count +=1

    # use punctuation to find sentences
    elif i in sentence_punctuation:
        sentence_count += 1

#print(word_count)

#print(sentence_count)

#print(letter_count)

L = letter_count / (word_count/ 100)

#print(L)

S = sentence_count / (word_count / 100)

#print(S)

cl_index = (0.0588 * L) - (0.296 * S) - 15.8

#print(cl_index)


if cl_index < 1:
    print("Before Grade 1")
elif cl_index > 15:
    print("Grade 16+")
else:
    print(f"Grade {round(cl_index)}")