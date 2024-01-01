#include <string>
#include "FileManagement.h"

std::string FileManagement::get_database_directory() {
  return database_directory;
}

std::string FileManagement::get_database_filename() {
  return database_filename;
}