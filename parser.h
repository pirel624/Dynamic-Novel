#ifndef PARSER

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

namespace utility
{
    std::vector<std::string> parse_file(std::string FileName)
    {
        std::vector<std::string> complete_string;
        std::string buffer_string;
        std::ifstream file;
        file.open("pirel.txt");
        while(std::getline(file, buffer_string))
        {
            complete_string.push_back(buffer_string);
        }
        return complete_string;
    }

    std::vector<std::string> parse_to_token(std::vector<std::string> parsed_file)
    {
        std::vector<std::string> token_bucket;
        std::string string_buffer;

        for(std::string line: parsed_file)
        {
            for(char character: line)
            {
                //if the iterator encounter a whitespace, a "word" or token is collected from the buffer, then the buffer is cleared
                if(character == ' ') 
                {
                    token_bucket.push_back(string_buffer);
                    string_buffer.clear();
                }
                //if not, then read each character and store them in the buffer
                else
                {
                    string_buffer = string_buffer + character;
                }
            }

            //For each newline, the buffer data is stored to the bucket and the buffer is cleared.
            //Thus, every end of the line word wont be jointed as a single token with starting word of the next line
            token_bucket.push_back(string_buffer);
            string_buffer.clear();
        }

        //this tokens only contains words. Thus empty string will be excluded
        std::vector<std::string> clean_tokens;
        for(int n = 0; n < token_bucket.size(); n++)
        {
            if(token_bucket[n].size() == 0){} // if it encounter an "empty" token, it wont be collected
            else
            {
                clean_tokens.push_back(token_bucket[n]);
            }
        }

        return clean_tokens;
    }

    std::vector<std::string> parse_string_to_token(std::string string)
    {
        string += " ";
        std::vector<std::string> token_bucket;
        std::string string_buffer;

        for(char character_buffer: string)
        {
            if(character_buffer == ' ')
            {
                token_bucket.push_back(string_buffer);
                string_buffer.clear();
            }
            else
            {
                string_buffer += character_buffer;
            }
        }

        //this tokens only contains words. Thus empty string will be excluded
        std::vector<std::string> clean_tokens;
        for(int n = 0; n < token_bucket.size(); n++)
        {
            if(token_bucket[n].size() == 0){} // if it encounter an "empty" token, it wont be collected
            else
            {
                clean_tokens.push_back(token_bucket[n]);
            }
        }

        return clean_tokens;
    }




}
#define PARSER ACTIVATED

#endif