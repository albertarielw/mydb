#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include <vector>
#include "Config.h"

class FileManagement {
public:
  FileManagement(Config & config);

  std::vector<std::string> read();

private:
  std::string database_directory, database_filename;
};

#endif
