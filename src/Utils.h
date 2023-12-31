#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <string>

std::chrono::time_point<std::chrono::system_clock> get_current_timestamp();
std::chrono::time_point<std::chrono::system_clock> get_expiry_timestamp(const int & duration_in_milisecond);
int convert_to_unix_timestamp(const std::chrono::time_point<std::chrono::system_clock> & timestamp);
std::string convert_to_lowercase(const std::string & input);

#endif
