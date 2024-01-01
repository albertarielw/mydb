#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include "ArgsParser.h"

std::unordered_map<std::string, std::vector<std::string>> ArgsParser::parse(int & argc, char ** argv) {
  std::vector<std::string> argv_vector;
  for (int i = 0; i < argc; ++i) {
    std::string line(argv[i]);
    argv_vector.push_back(line);
  }
  
  std::unordered_map<std::string, std::vector<std::string>> output;
  std::string key = "";
  std::vector<std::string> value;

  int index = 0;
  while (index < argc) {
    if (argv_vector[index].substr(0, 2) == "--") {
      if (key != "") {
        output[key] = value;
      }

      key = argv_vector[index].substr(2, argv_vector[index].length() - 2);
      value.clear();
    } else {
      value.push_back(argv_vector[index]);
    }

    index++;
  }

  if (key != "") {
    output[key] = value;
  }

  return output;
}