#include <iostream>

namespace utility
{
    void print_character_code()
    {
        for(int i = 0; i < 256; i++)
        {
            std::cout << i << "      " << static_cast<char>(i) << std::endl; 
        }
    }
}
