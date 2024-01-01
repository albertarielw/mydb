#include <string>
#include "Config.h"

std::string Config::get_database_directory() {
  return database_directory;
}

std::string Config::get_database_filename() {
  return database_filename;
}