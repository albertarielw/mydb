#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include "Config.h"

class FileManagement {
public:
  FileManagement(Config & config) {
    database_directory = config.get_database_directory();
    database_filename = config.get_database_filename();
  }

private:
  std::string database_directory, database_filename;
};

#endif
