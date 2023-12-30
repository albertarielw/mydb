#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <unistd.h>

class SocketManager {
public:
  void setup_socket();
  void close_socket();

  void accept_connection(int & socket_fd);

  ssize_t recv_msg(const int & socket_fd, char * msg, const int length);
  ssize_t send_msg(const int & socket_fd, const char * msg);

private:
  int socket_manager_fd;
};

#endif
