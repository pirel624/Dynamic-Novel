#ifndef MATRIX

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

namespace utility
{
    class screen
    {
        public:
        static const int X_SIZE = 100;
        static const int Y_SIZE = 50;
        static const int WHITE_CELL_1_CODE = 219;
        static const int WHITE_CELL_2_CODE = 178;
        static const int WHITE_CELL_3_CODE = 177;
        static const int WHITE_CELL_4_CODE = 176;

        private:
        char character_map[X_SIZE][Y_SIZE];

        public:

        screen()
        {
            for(int y = 0; y < Y_SIZE; y++)
            {
                for(int x = 0; x < X_SIZE; x++)
                {
                    character_map[x][y] = ' ';
                }
            }
            std::cout.setf(std::ios::unitbuf);
        }

        void clean()
        {
            for(int y = 0; y < Y_SIZE; y++)
            {
                for(int x = 0; x < X_SIZE; x++)
                {
                    character_map[x][y] = ' ';
                }
            }
        }

        void display()
        {
            const char BORDER = static_cast<char>(WHITE_CELL_1_CODE);

            //Upper Border
            for(int up = 0; up < X_SIZE + 2; up++)
            {
                std::cout << BORDER;
            }
            std::cout << '\n';

            //Body
            for(int y = 0; y < Y_SIZE; y++)
            {
                std::cout << BORDER;                       //Left Border
                for(int x = 0; x < X_SIZE; x++)
                {
                    std::cout << character_map[x][y];
                }
                std::cout << BORDER;                       //Right Border
                std::cout << '\n';                      //New Line
            }

            //Lower Border
            for(int down = 0; down < X_SIZE + 2; down++)
            {
                std::cout << BORDER;
            }
            std::cout << '\n';
        }

        bool edit(int pos_x, int pos_y, char character)
        {
            if(pos_x <= X_SIZE && pos_y <= Y_SIZE && pos_x >= 1 && pos_y >= 1)
            {
                character_map[pos_x - 1][pos_y - 1] = character;
                return true;
            }else{return false;}
        }

        static void inline window_clear_screen()
        {
            system("cls");
        }
    };
}
#define MATRIX ACTIVATED

#endif

