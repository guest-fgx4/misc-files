#include <stdio.h>

int main()
{

    int d = 0;
    int a1, a2 = 0;

    scanf("%d", &d); getchar();

    for (int i = 0; i < d; i++)
    {
        scanf("%d %d", &a1, &a2); getchar();

        int a3 = (a2 - a1);

        if (a3 == 0 && a1 == a2 && a1 == 1)
        {
            printf("%d\n", 1);
        }
        else
        {
            printf("%d\n", a3);
        }
    }
    

    return 0;
}
