#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "Server.h"
#include "ArgsParser.h"

/*
TODO:
- improve recv_msg logic
- implement optional for DB?
*/

int main(int argc, char ** argv) {
  ArgsParser args_parser;
  std::unordered_map<std::string, std::vector<std::string>> output = args_parser.parse(argc, argv);

  for (auto &[k, v]: output) {
    std::cout << k << " : ";
    for (auto &i: v) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  }

  Server server;
  server.serve();
}