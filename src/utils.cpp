#include "utils.h"

std::string getCurrTime()
{
    // Get the current time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the current time to a string
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), "%Y%m%d_%H%M%S");
    std::string currentTimeStr = ss.str();

    return currentTimeStr;
}
