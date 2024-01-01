#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
public:
  Config(std::unordered_map<std::string, std::vector<std::string>> & configs);

  std::string get_config(std::string & key);

private:
  std::string database_directory, database_filename;
  const std::string KEY_NAME_DATABASE_DIRECTORY = "dir";
  const std::string KEY_NAME_DATABASE_FILENAME = "dbfilename";
};

#endif