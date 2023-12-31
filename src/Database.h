#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <chrono>
#include <unordered_map>

class Database {
public:
  void set(const std::string & key, const std::string & value);
  void set_with_expiry(const std::string & key, const std::string & value, const int & expiry_duration_in_milisecond);
  std::string get(const std::string & key);

private:
  std::unordered_map<std::string, std::string> database;
  std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> expiry;
};

#endif
