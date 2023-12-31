#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <cstring>
#include "SocketManager.h"

class Service {
public:
  void dispatcher(SocketManager & socket_manager, const int & socket_fd, char * msg);

private:
  bool is_pong_service(char * msg);
  void pong_service(SocketManager & socket_manager, const int & socket_fd);
};

#endif
