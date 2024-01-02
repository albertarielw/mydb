#include <iostream>
#include <string>
#include <fstream>
#include <vector>
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
    std::cout << ch << " " << isalpha(ch) << std::endl;
  }
  std::cout << std::endl;

  // Close the file
  file.close(); 
}

std::string FileManagement::readFileAndGetKeys() {
  std::string filePath = database_directory + "/" + database_filename;
  std::fstream fs;
  fs.open(filePath, fs.binary | fs.in);
  if (fs.is_open()) {
    fs.seekg(0, std::ios::end);
    auto fileSize = fs.tellg();
    fs.seekg(0, std::ios::beg);
    // read the data:
    std::vector<unsigned char> fileData(fileSize);
    fs.read((char *)&fileData[0], fileSize);
    char delimiter = '@';
    int delimiterIndex = -1;
    std::string value;
    for (int i = 0; i < fileData.size(); i++)
    {
      if (delimiterIndex < 0)
      {
        if (fileData[i] == '@')
          delimiterIndex = i;
        else
          continue;
      }
      else
      {
        if (isalpha(fileData[i]))
          value += fileData[i];
        else
        {
          if (value == "")
            continue;
          break;
        }
      }
    }
    if (value != "")
      return "*1\r\n$" + std::to_string(value.length()) + "\r\n" + value + "\r\n";
    return "";
  }
  return "";
}