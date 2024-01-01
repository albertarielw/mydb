#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "SocketManager.h"
#include "Database.h"
#include "Config.h"

class Server {
public:
  Server(Config & config);
  void serve();

private:
  void setup_server();
  void close_server();
  
  void main_service(int socket_fd);

  SocketManager socket_manager;
  Database database;
  Config config;
};

#endif
