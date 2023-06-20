#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <iomanip> 
#include <sstream>

#define PACKET_SIZE 1472
#define STREAM_SIZE 20000
#define STREAM_FRAME_RATE 10



std::time_t getCurrDatetime();
std::string getCurrDatetimeStr();
std::string datetimeToFilename();

int ceilDiv(int numerator, int denominator);

std::string substrRightOf(std::string str, std::string pattern);

void appUsage();

#endif