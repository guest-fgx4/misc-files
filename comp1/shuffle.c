#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main ()
{

    short sampleSize = 0;
    int size = 0;
    int blueScore = 0;
    int redScore = 0;
    char blue[10000];
    char red[10000];
    // char sizeArray[4];
    
    scanf("%d", &sampleSize); getchar();

    
    for(int i; i < sampleSize; i++)
    {

        scanf("%d", &size); getchar();

        // scanf("%s", red); getchar();
        fgets(red, sizeof(red), stdin);
        //scanf("%s", blue); getchar();
        fgets(blue, sizeof(blue), stdin);

        for(int j = 0; j < size; j++)
        {
            if(!(red[j] == blue[j]))
            {
                if(red[j] > blue[j])
                {
                    redScore++;
                }
                else
                {
                    blueScore++;
                }
            }
        }

        if (redScore > blueScore)
        {
            printf("RED\n");
        }
        else
        {
            if (redScore == blueScore)
            {
                printf("EQUAL\n");
            }
            else
            {
                printf("BLUE\n");
            }
        }

        redScore = 0;
        blueScore = 0;
    }

    return 0;
}
