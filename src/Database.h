#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>

class Database {
public:
  void set(const std::string & key, const std::string & value);
  void set_with_expiry(const std::string & key, const std::string & value, const int & expiry_duration_in_milisecond);
  std::string get(const std::string & key);
  
  void update(std::unordered_map<std::string, std::string> & new_database, std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> & new_expiry);
  std::vector<std::string> get_all_keys();

private:
  std::unordered_map<std::string, std::string> database;
  std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> expiry;
};

#endif
