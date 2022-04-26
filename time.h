#ifndef TIME

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>


namespace utility
{
    void sleep_second(int seconds)
    {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    void sleep_milisecond(int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}
#define TIME ACTIVATED

#endif

