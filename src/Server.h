#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <vector>
#include <mutex>
#include "Server.h"
#include "SocketManager.h"

class Server {
public:
  void run();
  SocketManager spawn_new_socket_manager();

private:
  std::vector<SocketManager> socket_managers;
  std::mutex socket_managers_mutex;
};

#endif
