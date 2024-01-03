#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "Server.h"
#include "ArgsParser.h"
#include "Config.h"
#include "FileManagement.h"
/*
TODO:
- improve recv_msg logic
- implement optional for DB?
*/

int main(int argc, char ** argv) {
  ArgsParser args_parser;
  std::unordered_map<std::string, std::vector<std::string>> config_args = args_parser.parse(argc, argv);

  Config config(config_args);

  if (config.get_database_directory() != "" and config.get_database_filename() != "") {
    FileManagement file_management(config);
    file_management.print();

    std::unordered_map<std::string, std::string> data = file_management.load_data();
    std::cout << "data: " << std::endl;

    for (auto &[k, v]: data) {
      std::cout << k << " " << v << std::endl;
    }
  }

  Server server(config);
  server.serve();

  // FileManagement file_management(config);
  // std::vector<std::string> content = file_management.read();

  // for (int i = 0; i < content.size(); ++i) {
  //   std::cout << content[i] << std::endl;
  // }
}