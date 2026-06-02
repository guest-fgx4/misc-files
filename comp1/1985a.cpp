#include <stdio.h>

#include <string>
#include <iostream>

int main()
{
    std::string line;
    int n = 0;

    scanf("%d", &n); getchar();

    for(int i = 0; i < n; i++)
    {
        std::getline(std::cin, line);

        int y = 0;

        while (line[y] != ' ')
        {
            y++;
        }

        char c = line[0];
        char aux = line[y + 1];
        line[0] = aux; line[y + 1] = c;

        std::cout << line << std::endl;
    }

    return 0;
}
