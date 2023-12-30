#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <iostream>
#include <unistd.h>

enum ConnectionState {
  NOT_CONNECTED,
  CONNECTED
};

class SocketManager {
public:
  void start();
  void stop();

  ConnectionState get_connection_state() {
    return connection_state;
  }

  ssize_t recv_msg(char * msg);
  ssize_t send_msg(const char * msg);

private:
  int socket_fd;
  ConnectionState connection_state = NOT_CONNECTED;
  const int MAX_MSG_BYTES = 1024;
};

#endif
