#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");

    int letter = 0;
    int words = 0;
    int sentence = 0;
    for (int i = 0, L = strlen(text); i<L; i++)
    {
        if (isalpha(text[i]))
        {
            letter ++;
        }

        if (isspace(text[i]))
        //利用空格来检测,空格数量+1
        //但是要确保won't start or end with a word
        {
            words ++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence ++;
        }
    }
    float S = ((float)sentence / (words + 1)) * 100.0;
    float L = ((float)letter / (words + 1)) * 100.0;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}