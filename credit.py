from cs50 import get_string


def main():
    # Get input sentence from user
    text = get_string("Text: ")

    # declares variables for sentences, words and letters
    sentences = 0
    words = 0
    letters = 0

    # Loops over the text and checks what happens
    for i in range(0, len(text)):
        # Converts to upper to make a better comparison
        letter = text[i].upper()
        if (letter >= 'A' and letter <= 'Z'):
            letters += 1
        elif (letter == ' ' and text[i - 1].upper() >= 'A' and text[i - 1].upper() <= 'Z'):
            words += 1
        elif (letter == ',' and text[i - 1].upper() >= 'A' and text[i - 1].upper() <= 'Z'):
            words += 1
        elif (letter == '.' or letter == '!' or letter == '?'):
            if (text[i - 1].upper() >= 'A' and text[i - 1].upper() <= 'Z'):
                sentences += 1
                words += 1
    calculate_score(sentences, words, letters)


# Prints the grade
def calculate_score(sentences, words, letters):
    # Converts to float
    words_float = words * 1.0
    L = letters / words_float * 100.0
    S = sentences / words_float * 100.0
    # printf("L: %f, S: %f", L, S)
    grade = 0.0588 * L - 0.296 * S - 15.8
    grade_rounded = round(grade)
    if (grade < 1):
        print("Before Grade 1")
    elif (grade >= 16):
        print("Grade 16+")
    else:
        print("Grade " + str(grade_rounded))


if __name__ == "__main__":
    main()
