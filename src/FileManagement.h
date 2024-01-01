#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include "Config.h"

class FileManagement {
public:
  FileManagement(Config & config);

private:
  std::string database_directory, database_filename;
};

#endif
