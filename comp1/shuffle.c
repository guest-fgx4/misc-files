#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main ()
{

    short sampleSize = 0;
    int size = 0;
    int blueScore = 0;
    int redScore = 0;
    char blue[1000];
    char red[1000];
    char sizeArray[4];
    
    scanf("%1d", &sampleSize); getchar();

    
    scanf("%1d", &size); getchar();
    for(int i; i < sampleSize; i++)
    {

       // scanf("%s", red); getchar();
       fgets(red, size, stdin);
       //scanf("%s", blue); getchar();
       fgets(blue, size, stdin);

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
       scanf("%1d", &size);
    }

    return 0;
}
