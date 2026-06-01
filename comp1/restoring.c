#include <stdio.h>

#define SIZE 4

int main ()
{

    unsigned int input[SIZE];
    unsigned int outputa, outputb, outputc = 0;

    for (size_t i = 0; i < SIZE; i++)
    {
        scanf("%d", &input[i]); getchar();
    }

    //for (size_t i = 0; i < 4; i++)
    //{
    //    printf("%d\n", input[i]); 
    //}

    unsigned int bigger = 0;
    unsigned int smaller = 0xffffffff;
    unsigned int secBigger = 0;

    for(int i = 0; i < 4; i++)
    {
        if (bigger < input[i])
        {
            bigger = input[i];
        }
        if (smaller > input[i])
        {
            smaller = input[i];
        } 
    }


    for(int i = 0; i < 4; i++)
    {
        if (secBigger < input[i] && input[i] < bigger)
        {
            secBigger = input[i];
        }
    }

    // printf("%d %d %d\n", bigger, smaller, secBigger);

    outputa = bigger - secBigger;
    outputb = bigger - smaller;
    outputc = bigger - (outputa + outputb);

    printf("%d %d %d", outputa, outputb, outputc);

    // difference

    // printf("Testing... %d%d%d%d\n", inputa, inputb, inputc, inputd);
    //
    return 0;
}
