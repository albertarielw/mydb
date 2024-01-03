#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
#include "SocketManager.h"
#include "Database.h"
#include "Utils.h"
#include "Config.h"
#include "FileManagement.h"

class Service {
public:
  void dispatcher(SocketManager & socket_manager, const int & socket_fd, const std::string & input, Database & database, Config & config, FileManagement & file_management);

private:

  std::vector<std::string> deserialize(const std::string & input);
  std::string extract_command(const std::vector<std::string> & deserialized_input);
  void encode_bulk_string(std::string &resp, const std::string &str);

  bool is_pong_service(const std::string & command);
  void pong_service(SocketManager & socket_manager, const int & socket_fd);

  bool is_echo_service(const std::string & command);
  void echo_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input);

  bool is_set_service(const std::string & command);
  void set_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Database & database);

  bool is_get_service(const std::string & command);
  void get_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Database & database);

  bool is_set_service_with_expiry(const std::string & command, const std::vector<std::string> & deserialized_input);
  void set_service_with_expiry(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Database & database);
  
  bool is_config_service(const std::string & command);

  bool is_config_get_service(const std::string & command, const std::vector<std::string> & deserialized_input);
  std::string encode_config_get_response(const std::string &key, const std::string &value);
  void config_get_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Config & config);

  bool is_keys_service(const std::string & command);
  
  bool is_get_all_keys_service(const std::string & command, const std::vector<std::string> & deserialized_input);
  void get_all_keys_service(SocketManager & socket_manager, const int & socket_fd, Database & database);
};

#endif
