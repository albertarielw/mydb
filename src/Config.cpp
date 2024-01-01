#include <string>
#include <unordered_map>
#include "Config.h"

Config::Config(std::unordered_map<std::string, std::vector<std::string>> & configs) {
  if (configs.find(KEY_NAME_DATABASE_DIRECTORY) != configs.end()) {
    database_directory = configs[KEY_NAME_DATABASE_DIRECTORY][0];
  }

  if (configs.find(KEY_NAME_DATABASE_FILENAME) != configs.end()) {
    database_filename = configs[KEY_NAME_DATABASE_FILENAME][0];
  }
}

std::string Config::get_database_directory() {
  return database_directory;
}

std::string Config::get_database_filename() {
  return database_filename;
}