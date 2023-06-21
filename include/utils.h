#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <iomanip> 
#include <sstream>

#define PACKET_SIZE 1472
#define STREAM_SIZE 20000
#define STREAM_FRAME_RATE 10

#define CLIENT_PORT 5000
#define SERVER_PORT 5005

std::time_t getCurrDatetime();
std::string getCurrDatetimeStr();
std::string datetimeToFilename();

int ceilDiv(int numerator, int denominator);

std::string substrRightOf(std::string str, std::string pattern);

void appUsage();

#endif