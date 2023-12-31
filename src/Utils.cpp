#include <chrono>
#include "Utils.h"

std::chrono::time_point<std::chrono::system_clock> get_current_timestamp() {
  return std::chrono::system_clock::now();
}

std::chrono::time_point<std::chrono::system_clock> get_expiry_timestamp(const int & duration_in_milisecond) {
  return std::chrono::system_clock::now() + std::chrono::milliseconds(duration_in_milisecond);
}

int convert_to_unix_timestamp(const std::chrono::time_point<std::chrono::system_clock> & timestamp) {
  auto duration = timestamp.time_since_epoch();
  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
  return seconds.count();
}

std::string convert_to_lowercase(const std::string & input) {
  std::string output = "";
  for (auto &c: input) {
    output += tolower(c);
  }
  return output;
};