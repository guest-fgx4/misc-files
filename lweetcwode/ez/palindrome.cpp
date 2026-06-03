#include <iostream>
#include <string>

int main(int argc, char* argv[])
{


    // int x = (int)(argv[0]);


    std::string string = std::to_string(101);
    bool res = true;

    size_t i = 0;
    size_t j = string.size() - 1;


    std::cout <<  j << std::endl;

    while(i <= j && res)
    {
        if (string[i] != string[j]) res = false;
        i++;
        j--;
    }

    if (res)
    {
        std::cout << "True!" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
    return 0;
}
