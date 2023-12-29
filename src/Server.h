#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "SocketManager.h"

class Server {
public:
  void run();

private:
  SocketManager socket_manager;
};

#endif
