#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
public:
  Config(const std::string& database_directory, const std::string& database_filename)
    : database_directory(database_directory), database_filename(database_filename) {}

  std::string get_database_directory();
  std::string get_database_filename();

private:
  std::string database_directory, database_filename;
};

#endif
