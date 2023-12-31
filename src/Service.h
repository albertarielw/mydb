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

  bool is_pong_service(const std::vector<std::string> & input);
  void pong_service(SocketManager & socket_manager, const int & socket_fd);
};

#endif
