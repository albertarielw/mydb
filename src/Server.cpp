#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include "Server.h"
#include "SocketManager.h"

void Server::serve() {
  setup_server();

  service();

  close_server();
}

void Server::setup_server() {
  socket_manager.setup_socket_manager();
}

void Server::close_server() {
  socket_manager.close_socket_manager();
}

void Server::service() {
  int socket_fd = socket_manager.create_new_connection();

  while (true) {
    const int MSG_SIZE_MAX = 1024;
    char msg[MSG_SIZE_MAX];
    ssize_t bytes_recv = socket_manager.recv_msg(socket_fd, msg, MSG_SIZE_MAX);

    if (bytes_recv <= 0) {
      std::cout << "Client disconnected\n";
      if (socket_fd != -1) {
        close(socket_fd);
      }
      break;
    }

    const char *PING_MSG = "ping";
    char *t; 
    
    const char* PONG_MSG = "+PONG\r\n";
    for (t = msg; *t != '\0'; t++) {
      if (*t == 'p' && strncmp(t, PING_MSG, strlen(PING_MSG)) == 0) {
        socket_manager.send_msg(socket_fd, PONG_MSG);
      }
    }
  }
}

// void Server::run() {
//   while (true) {
//     int socket_fd = socket_manager.listen_for_connection();

//     const int MSG_SIZE_MAX = 1024;
//     char msg[MSG_SIZE_MAX];
//     ssize_t bytes_recv = socket_manager.recv_msg(socket_fd, msg, MSG_SIZE_MAX);

//     if (bytes_recv <= 0) {
//       std::cout << "Client disconnected\n";
//       if (socket_fd != -1) {
//         close(socket_fd);
//       }
//       break;
//     }

//     const char *PING_MSG = "ping";
//     char *t; 
    
//     const char* PONG_MSG = "+PONG\r\n";
//     for (t = msg; *t != '\0'; t++) {
//       if (*t == 'p' && strncmp(t, PING_MSG, strlen(PING_MSG)) == 0) {
//         socket_manager.send_msg(socket_fd, PONG_MSG);
//       }
//     }
//   }
// }


// void Service::serve() {
//   SocketManager socket_manager;

//   socket_manager.setup_socket();

//   // main logic
//   while (true) {
//     int socket_fd = -1;
//     socket_manager.accept_connection(socket_fd);

//     const int MSG_SIZE_MAX = 1024;
//     char msg[MSG_SIZE_MAX];
//     ssize_t bytes_recv = socket_manager.recv_msg(socket_fd, msg, MSG_SIZE_MAX);

//     if (bytes_recv <= 0) {
//       std::cout << "Client disconnected\n";
//       if (socket_fd != -1) {
//         close(socket_fd);
//       }
//       break;
//     }

//     const char *PING_MSG = "ping";
//     char *t; 
    
//     const char* PONG_MSG = "+PONG\r\n";
//     for (t = msg; *t != '\0'; t++) {
//       if (*t == 'p' && strncmp(t, PING_MSG, strlen(PING_MSG)) == 0) {
//         socket_manager.send_msg(socket_fd, PONG_MSG);
//       }
//     }
//   }

//   socket_manager.close_socket();
// }
