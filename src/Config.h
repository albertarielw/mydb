#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <unordered_map>

class Config {
public:
  Config(std::unordered_map<std::string, std::vector<std::string>> & configs);

  std::string get_config(std::string & key);

  std::string get_database_directory();
  std::string get_database_filename();

private:
  std::string database_directory = "", database_filename = "";
  const std::string KEY_NAME_DATABASE_DIRECTORY = "dir";
  const std::string KEY_NAME_DATABASE_FILENAME = "dbfilename";
};

#endif
