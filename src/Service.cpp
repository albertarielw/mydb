#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include "Service.h"
#include "SocketManager.h"

void Service::serve() {
  SocketManager socket_manager;

  socket_manager.start();

  // main logic
  while (true) {
    const int MSG_SIZE_MAX = 1024;
    char msg[MSG_SIZE_MAX];
    ssize_t bytes_recv = socket_manager.recv_msg(msg, MSG_SIZE_MAX);

    if (bytes_recv <= 0) {
      std::cout << "Client disconnected\n";
      break;
    }

    const char *PING_MSG = "ping";
    char *t; 
    
    const char* PONG_MSG = "+PONG\r\n";
    for (t = msg; *t != '\0'; t++) {
      if (*t == 'p' && strncmp(t, PING_MSG, strlen(PING_MSG)) == 0) {
        socket_manager.send_msg(PONG_MSG);
      }
    }
  }

  socket_manager.stop();
}
