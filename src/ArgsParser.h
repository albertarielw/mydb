#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>

class ArgsParser {
public:
  std::unordered_map<std::string, std::vector<std::string>> parse(int & argc, char ** argv);

private:
};

#endif
