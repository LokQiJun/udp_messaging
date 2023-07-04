#include "utils.h"

#include <iostream>



std::time_t getCurrDatetime()
{
    // Get the current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    return currentTime;
}

std::string getCurrDatetimeStr()
{
    std::stringstream ss;
    std::time_t currDatetime = getCurrDatetime();
    ss << std::put_time(std::localtime(&currDatetime), "%Y-%m-%d %H:%M:%S");
    std::string currentDateTimeStr = ss.str();
    return currentDateTimeStr;
}

std::string datetimeToFilename()
{
    std::stringstream ss;
    std::time_t currDatetime = getCurrDatetime();
    ss << std::put_time(std::localtime(&currDatetime), "%Y%m%d_%H%M%S");
    std::string filename = ss.str();
    return filename;
}

int ceilDiv(int numerator, int denominator)
{   
    return numerator/denominator + (numerator%denominator != 0);
}


std::string substrRightOf(std::string str, std::string pattern)
{
    std::size_t found = str.find_last_of(pattern);

    // Strip parent directories, if any
    if(found != std::string::npos)
    {
        str = str.substr(found + 1);
    } 
    
    return str;
}

void appUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "-TS : Text Send mode" << std::endl;
    std::cout << "-TR : Text Receive mode" << std::endl;
    std::cout << "-FS : File Send mode" << std::endl;
    std::cout << "-FR : File Receive mode" << std::endl;
    std::cout << "-U : Stream upload mode " << std::endl;
    std::cout << "-D : Stream download mode " << std::endl;
}