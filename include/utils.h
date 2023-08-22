#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <iomanip> 
#include <sstream>

#ifndef CLIENT_PORT
#define CLIENT_PORT 5000
#endif
#ifdef SERVER_PORT
#define SERVER_PORT 5005
#endif

// Application constants
#define PACKET_SIZE 1472

// Utility datetime funcitons
std::time_t getCurrDatetime();
std::string getCurrDatetimeStr();
std::string datetimeToFilename();

// Helper functions
int ceilDiv(int numerator, int denominator);

std::string substrRightOf(std::string str, std::string pattern);
std::string substrLeftOf(std::string str, std::string pattern);

// Application usage instructions
void appUsage();

#endif
