#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <thread>
#include <unistd.h>

class SocketManager {
public:
  void setup_socket_manager();
  void close_socket_manager();

  int create_new_connection();

  ssize_t recv_msg(const int & socket_fd, char * msg, const int length);
  ssize_t send_msg(const int & socket_fd, const char * msg);

private:
  int socket_manager_fd;
};

#endif
