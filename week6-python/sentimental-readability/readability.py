from cs50 import get_string
import string

''' Coleman-Liau = 0.0588 * L - .296 * S - 15.8
    L = letters / total words * 100
    S = sentences / total words * 100
'''
# Words are # of spaces and punctuation (. or ! or ?)
# Sentences are number of punctuation marks
words = 1
sentences = 0
letters = 0

# Getting user input text
text = get_string("Text: ")

# Looping through text one character at a time and validating is letter, is punctuation (discluding ","), is space, respectively
for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i] == "!" or text[i] == "." or text[i] == "?":
        sentences += 1
    elif text[i] == " ":
        words += 1

# Accounting for single-word input
if sentences == 0:
    sentences = 1

# Coleman-Liau = 0.0588 * L - .296 * S - 15.8
avg_letters = float(letters / words * 100)
avg_sentences = float(sentences / words * 100)
colemanliau = round(0.0588 * (float(letters) / float(words) * 100) - 0.296 * (float(sentences) / float(words) * 100) - 15.8)

if colemanliau >= 16:
    print("Grade 16+")
elif colemanliau < 1:
    print("Before Grade 1")
else:
    print(f"Grade {colemanliau}")
