//
// Created by iyang on 2017/8/13.
//

#include <iostream>

int main()
{
    char digit_table[] = "0123456789abcdef";
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            std::cout << '\'' << digit_table[x] << "\', \'" << digit_table[y] << "\', ";
        }
        std::cout << std::endl;
    }
    return 0;
}