#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <cstring>
#include "SocketManager.h"

class Service {
public:
  void pong_service(SocketManager & socket_manager, const int & socket_fd, char * msg);
private:
};

#endif
