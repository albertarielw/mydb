#ifndef SERVICE_H
#define SERVICE_H

#include <vector>
#include <string>
#include <cstring>
#include "SocketManager.h"

class Service {
public:
  void dispatcher(SocketManager & socket_manager, const int & socket_fd, char * msg);

private:
  std::vector<std::string> deserialize(const std::string & input);
  std::string extract_command(const std::vector<std::string> & deserialized_input);

  bool is_pong_service(const std::string & command);
  void pong_service(SocketManager & socket_manager, const int & socket_fd);

  bool is_echo_service(const std::string & command);
  void echo_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input);
};

#endif
