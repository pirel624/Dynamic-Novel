#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

#include "screen.h"
#include "time.h"
#include "parser.h"
#include "char_code.h"

/*
in context of void writer();
console width breaching is a possibility
so.....fuck.....

# setw(n) >> n - 1 offset
*/

void writer(std::vector<std::string> array_of_line, int speed, bool justify_right = false, int tabs = 10)
{
    utility::sleep_milisecond(speed);// just in case array_of_line is empty, and the only purpose of calling this function is to delay writing

    if(justify_right)
    {
        std::cout << std::setw(tabs + 1);
    }

    for(std::string line: array_of_line)
    {
        for(char character: line)
        {
            std::cout << character;
            utility::sleep_milisecond(speed);
        }
        std::cout << std::endl;
        if(justify_right)
        {
            std::cout << std::setw(tabs + 1);
        }
    }

    if(justify_right)
    {
        std::cout << std::setw(0);
    }
}

struct instruction
{
    bool right_justify = false;
    int delay = 0;
    std::vector<std::string> text;

    void reset()
    {
        right_justify = false;
        delay = 0;
        text.clear();
    }
};


int main()
{
    std::vector<std::string> parsed_data = utility::parse_file("data.txt");

    std::vector<instruction> instruction_set;
    std::vector<std::string> tokens;
    instruction compiled_data;
    bool is_compiling = false;      // determine whether the iteration is in "compiling" mode or not.

    // Translate parsed file to instruction set

    for(int n = 0; n < parsed_data.size(); n++)
    {
        tokens = utility::parse_string_to_token(parsed_data[n]);

        if(parsed_data[n].size() != 0)
        {
            if(tokens[0] == "[begin]")  // if iterator encounter begin signal
            {
                is_compiling = true;
                //tokens[1] -> compiled_data.delay
                compiled_data.delay = std::stoi(tokens[1]);

                //tokens[2] -> compiled_data.justify_right
                if(tokens[2] == "true")
                {
                    compiled_data.right_justify = true;
                }
                else
                {
                    compiled_data.right_justify = false;
                }
            }
            else if(tokens[0] == "[end]") // if iterator encounter end signal
            {
                is_compiling = false;
                instruction_set.push_back(compiled_data);
                compiled_data.reset();
            }
            else                    // if iterator encounter standard word/token 
            {
                if(is_compiling)
                {
                    compiled_data.text.push_back(parsed_data[n]);
                }
                else
                {
                    // do nothing
                }
            }
        }
        else
        {
            if(is_compiling)
            {
                compiled_data.text.push_back("");
            }
            else
            {
                    // do nothing
            }
        }
    }

    // do the instruction
    for(instruction command: instruction_set)
    {
        writer(command.text, command.delay, command.right_justify);
    }

    
    utility::sleep_second(1000);
    
    return 0;
}