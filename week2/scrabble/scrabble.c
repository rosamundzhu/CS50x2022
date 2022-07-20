#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int POINTS[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int compute_scores(string word);

int main(void)
{
    string word1 = get_string("Player1: ");
    string word2 = get_string("Player2: ");

    int score1 = compute_scores(word1);
    int score2 = compute_scores(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_scores(string word)
{
    int score = 0;
    for (int i = 0, len = strlen(word); i < len ; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i]-'A']; //变成01234
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i]-'a'];
        }
    }
    return score;
}