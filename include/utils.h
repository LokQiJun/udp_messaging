#include <chrono>
#include <iomanip> 
#include <sstream>

#define PACKET_SIZE 1024
#define STREAM_SIZE 65536
#define STREAM_FRAME_RATE 24

std::time_t getCurrDatetime();
std::string getCurrDatetimeStr();
std::string datetimeToFilename();

int ceilDiv(int numerator, int denominator);

void appUsage();
