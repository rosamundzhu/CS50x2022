#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        //check key length
        if (strlen(key) == 26)
        {
            //check for non-alphabetic characters
            //如果是用for遍历，不满足就直接退出，下面的code可以不用写在loop中
            for (int index = 0, len = strlen(key); index < len; index++)
            {
                if (!isalpha(key[index]))
                {
                    printf("Key must only contain 26 alphabetic characters.\n");
                    return 1;
                }
            }

            //check for repeated characters
            //case-insensitive
            for (int i = 0, len = strlen(key); i < (len - 1); i++)
            {
                char currentletter = key[i];
                for (int j = i + 1; j < len; j++)
                {
                    char nextletter = key[j];
                    if (tolower(currentletter) == tolower(nextletter))
                    {
                        printf("Key must not repeated characters.\n");
                        return 1;
                    }
                }
            }

            //满足不重复的条件
            string text = get_string("plaintext: ");
            for (int num = 0, l = strlen(text); num < l; num++)
            {
                if (isalpha(text[num]))
                {
                    char textletter = text[num];
                    int testlower = islower(textletter);
                    int testupper = isupper(textletter);
                    if (testupper > 0)
                    {
                        int j = text[num] - 65;
                        text[num] = toupper(key[j]);
                    }
                    else if (testlower > 0)
                    {
                        int j = text[num] - 97;
                        text[num] = tolower(key[j]);
                    }
                }
                //1. for each alphabetic character, determine which letter it maps to
                //2. preserve case
                //3. leave non-alpabetic character as - is
            }

            printf("ciphertext: %s\n", text);
            return 0; //注意这里是return 0
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}