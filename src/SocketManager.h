#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <unistd.h>

class SocketManager {
public:
  void start();
  void stop();

  ssize_t recv_msg(char * msg);
  ssize_t send_msg(const char * msg);

private:
  int socket_fd;
  const int MAX_MSG_BYTES = 1024;
};

#endif
