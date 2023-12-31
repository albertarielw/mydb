#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "SocketManager.h"

class Server {
public:
  void serve();

private:
  void setup_server();
  void close_server();
  
  void service_dispatcher(int socket_fd); //TODO: abstract out to service class

  SocketManager socket_manager;
};

#endif