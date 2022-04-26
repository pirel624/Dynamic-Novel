

// this library is currently hot functional


#include <iostream>
#include <string>
#include <vector>
#include "time.h"

void writer(std::vector<std::string> array_of_words, int speed, bool justify_right = false, int field_width = 100, int tabs = 20)
{
    /*
    For each line, it consists of tabs, words, and whitespace
    If the text is left justified, then the tabs would be equal to zero
    If the text is right justified the tabs might vary
    But for now, lets ignore the tabs and focus only on words and whitespaces.
    I myself model this words and whitespaces sequence as an array of a single word and a single whitespace
    But by doing so, on everyline, there would be a single whitespace sticking out at the end.
    For example:

    My_Name_Is_Pirel_    (the underscore represent a whitespace)

    But, what we actually want is:

    My_Name_Is_Pirel

    So essentially, we shall truncate the sticking whitespace.

    Another thing to consider is, given a space for writing per line (this would be: field_width - tabs)
    how should we fill those spaces without truncating a single word ?

    For example:

    My_Name_Is_Pir           // truncated word
    el

    The solution is to cut the sequences before the word that might be truncated

    So it should be like this:
    
    My_Name_Is
    Pirel

    So to summarize:
    1. Given a sequence of words and whitespaces, that can be modelled as an array of word-whitespace pair
    2. Given a set of "spaces" that can be used
    3. Truncate sticking whitespace at the end, and shove the content of the spaces forward by one unit (character)
    4. No word should be split
                                                                 what about \n ?
    The solution is:
    1. x is the amount of given spaces per line
    2. iterate forward and sum the size of each pair of word-whitespace, lets call this sum n
    3. stop the iteration if n is more than (x + 1)       // that one space will be filled with whitespace, which would be truncated
    4. now n is more than x + 1, so substract n by the size of the last iterated word-whitepace pair
    5. pull n amount from word and whitepaces sequence, then print it
    6. repeat*/
    
    std::vector<int> words_allocation;
    int spaces = field_width;
    int current_iteration_size = 0;
    int current_iteration_amount = 0;
    for(std::string buffer: array_of_words)
    {
        current_iteration_size += buffer.size() + 1;  // each word is paired with a single whitespace that follows it
        if(current_iteration_size > (spaces + 1)) // if current iteration excede space size + 1 (that "1" is for would be truncated whitespace)
        {
            // reset everything and store the words allocation data
            current_iteration_size = 0;
            words_allocation.push_back(current_iteration_amount);
            current_iteration_amount = 0;

            // begin again
            current_iteration_size += buffer.size() + 1;
            current_iteration_amount = 0;
        }
        else  // if not, increment the word allocation amount
        {
            current_iteration_amount++;
        }
    }

    std::vector<std::string> array_of_lines;
    std::string string_buffer;
    int iteration = 0;
    for(int buffer: words_allocation)
    {
        string_buffer.clear();
        for(int n = 0; n < buffer; n++)
        {
            iteration += n;
            string_buffer += (array_of_words[iteration] + " ");
        }
        string_buffer.pop_back(); // truncating whitespace
        array_of_lines.push_back(string_buffer);
    }

    for(std::string line_buffer: array_of_lines)
    {
        for(char character_buffer: line_buffer)
        {
            std::cout << character_buffer;
            utility::sleep_milisecond(speed);
        }
        std::cout << std::endl;
    }

}

