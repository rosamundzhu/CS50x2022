from cs50 import get_string

file = get_string("Text: ")
W = 0
L = 0
S = 0

for i in range(len(file)):
    if file[i].isspace() == True:
        W += 1
    if file[i].isalpha() == True:
        L += 1
    if file[i] in ['?', '.', '!']:
        S += 1
W += 1
L = L / W * 100
S = S / W * 100

# L is the average number of letters per 100 words in the text
# S is the average number of sentences per 100 words in the text.
# print(W, L, S)

index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
