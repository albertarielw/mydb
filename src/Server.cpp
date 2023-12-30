#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include "Server.h"
#include "SocketManager.h"

// void Server::run() {
//   SocketManager socket_manager;

//   while (true) {
//     if (socket_manager.get_is_connected()) {
//       socket_manager.start()
//     }
//   }
// }

// SocketManager Server::spawn_new_socket_manager() {
//   SocketManager socket_manager;

//   // lock with mutex
//   socket_managers_mutex.lock();
//   socket_managers.push_back(socket_manager);
//   socket_managers_mutex.unlock();

//   return socket_manager;
// }

//   socket_manager.start();

//   // main logic
//   while (true) {
//     const int MSG_SIZE_MAX = 1024;
//     char msg[MSG_SIZE_MAX];
//     ssize_t bytes_recv = socket_manager.recv_msg(msg);

//     if (bytes_recv <= 0) {
//       std::cout << "Client disconnected\n";
//       break;
//     }

//     const char *PING_MSG = "ping";
//     char *t; 
    
//     const char* PONG_MSG = "+PONG\r\n";
//     for (t = msg; *t != '\0'; t++) {
//       if (*t == 'p' && strncmp(t, PING_MSG, strlen(PING_MSG)) == 0) {
//         socket_manager.send_msg(PONG_MSG);
//       }
//     }
//   }

//   // close server
//   socket_manager.stop();
// }
