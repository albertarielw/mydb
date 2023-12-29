#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "SocketManager.h"

int main(int argc, char **argv) {
  SocketManager socket_manager;
  socket_manager.start();

  char msg[1024];
  socket_manager.recv_msg(msg);

  const char* PONG_MSG = "+PONG\r\n";
  socket_manager.send_msg(PONG_MSG);

  socket_manager.stop();
}
