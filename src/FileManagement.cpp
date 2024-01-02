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