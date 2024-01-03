#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include <vector>
#include "Config.h"

enum OP_CODE : unsigned char {
  OP_CODE_EOF = 0xFF,
  OP_CODE_SELECTDB = 0xFE,
  OP_CODE_EXPIRETIME = 0xFD,
  OP_CODE_EXPIRETIMEMS = 0xFC,
  OP_CODE_RESIZEDB = 0xFB,
  OP_CODE_AUX = 0xFA
};


class FileManagement {
public:
  FileManagement(Config & config);
  
  std::vector<std::string> read();
  void print();
  std::string readFileAndGetKeys();
  std::unordered_map<std::string, std::string> load_data();

private:
  std::string database_directory, database_filename;
  const std::vector<unsigned char> OP_CODES = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA};

  bool is_op_code(char & byte);
  std::string convert_op_codes_to_string(char & byte);
};

#endif
