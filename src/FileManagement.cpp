#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "FileManagement.h"
#include "Config.h"

FileManagement::FileManagement(Config & config) {
  database_directory = config.get_database_directory();
  database_filename = config.get_database_filename();
}

std::vector<std::string> FileManagement::read() {

  std::vector<std::string> content;

  // Open the file
  std::ifstream file(database_directory + "/" + database_filename);
  
  // Check if the file is open
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return content; // Return an empty vector if the file cannot be opened
  }

  // Read the content line by line
  std::string line;
  while (std::getline(file, line)) {
    content.push_back(line);
  }

  // Close the file
  file.close();

  return content;
}

bool FileManagement::is_op_code(char & byte) {
  std::vector<unsigned char> opCodes = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA};
  unsigned char byteValue = static_cast<unsigned char>(byte);
  for (int i = 0; i < opCodes.size(); ++i) {
    if (byteValue == opCodes[i]) {
      return true;
    }
  }
  return false;
}

std::string FileManagement::convert_op_codes_to_string(char & byte) {
  unsigned char byteValue = static_cast<unsigned char>(byte);
  switch (byteValue) {
    case OP_CODE_EOF:
      return "0xFF";
    case OP_CODE_SELECTDB:
      return "0xFE";
    case OP_CODE_EXPIRETIME:
      return "0xFD";
    case OP_CODE_EXPIRETIMEMS:
      return "0xFC";
    case OP_CODE_RESIZEDB:
      return "0xFB";
    case OP_CODE_AUX:
      return "0xFA";
    default:
      return "";
  }
}

void FileManagement::print() {
  std::ifstream file(database_directory + "/" + database_filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
  }

  // Read the file byte by byte
  std::cout << "file: " << std::endl;
  char ch;
  while (file.read(&ch, 1)) {
    // Print the integer value of the character without converting to string
    std::cout << "char: " << static_cast<unsigned char>(ch) << ", int: " << static_cast<int>(ch) << ", " << (is_op_code(ch) ? convert_op_codes_to_string(ch) : "") << std::endl;
  }
  std::cout << std::endl;

  // Close the file
  file.close(); 
}

std::string FileManagement::readFileAndGetKeys() {
  std::ifstream file(database_directory + "/" + database_filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
  }

  // Read the file byte by byte
  std::string key = "";
  bool op_code_FB_found = false;
  bool key_found = false;
  char ch;
  while (file.read(&ch, 1)) {
    if (!op_code_FB_found) {
      if (static_cast<unsigned char>(ch) == OP_CODE_RESIZEDB) {
        op_code_FB_found = true;
      }
      continue;
    }

    if (!key_found) {
      if (isalpha(ch)) {
        key_found = true;
        key += ch;
      }
      continue;
    }

    if (!isalpha(ch)) {
      break;
    }
    key += ch;
  }

  // Close the file
  file.close(); 

  return key;
}

void FileManagement::load_data(Database & database) {
  std::ifstream file(database_directory + "/" + database_filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }
  
  std::unordered_map<std::string, std::string> new_database;
  std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> new_expiry;
  char ch;
  while (file.read(&ch, 1)) {
    if (static_cast<unsigned char>(ch) == OP_CODE_EOF) {
      break;
    }

    if (static_cast<unsigned char>(ch) == OP_CODE_RESIZEDB) {
      std::vector<int> length_encoding_descriptor;
      for (int i = 0; i < 2; ++i) {
        file.read(&ch, 1);
        length_encoding_descriptor.push_back(static_cast<int>(ch));
      }

      int nums_of_keys = length_encoding_descriptor[0];
      for (int i = 0; i < nums_of_keys; ++i) {
        file.read(&ch, 1);

        bool has_expiry = false;
        unsigned long long num;
        if (static_cast<unsigned char>(ch) == OP_CODE_EXPIRETIME) {
          file.read(reinterpret_cast<char*>(&num), 4);
          std::cout << "expiry: " << num << " s" << std::endl;

          file.read(&ch, 1);

          has_expiry = true;
        } else if (static_cast<unsigned char>(ch) == OP_CODE_EXPIRETIMEMS) {
          file.read(reinterpret_cast<char*>(&num), 8);
          std::cout << "expiry: " << num << " ms" << std::endl;

          file.read(&ch, 1);

          has_expiry = true;
        }

        file.read(&ch, 1);
        int nums_of_bytes = static_cast<int>(ch);

        std::string key = "";
        for (int j = 0; j < nums_of_bytes; ++j) {
          file.read(&ch, 1);
          key += ch;
        }

        file.read(&ch, 1);
        nums_of_bytes = static_cast<int>(ch);

        std::string value = "";
        for (int j = 0; j < nums_of_bytes; ++j) {
          file.read(&ch, 1);
          value += ch;
        }

        new_database[key] = value;
        if (has_expiry) {
          auto expiry = std::chrono::time_point<std::chrono::system_clock>(
            std::chrono::milliseconds(num));
          new_expiry[key] = expiry;
        }
      }
    }
  }

  // Close the file
  file.close(); 

  database.update(new_database, new_expiry);

  print();
}