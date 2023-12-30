#ifndef SERVICE_H
#define SERVICE_H

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
  
  void service(); //TODO: abstract out to service class
  SocketManager socket_manager;
};

#endif
