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

void SocketManager::setup_socket_manager() {
  socket_manager_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_manager_fd < 0) {
    std::cerr << "Failed to create server socket\n";
    return;
  }
  
  // Since the tester restarts your program quite often, setting REUSE_PORT
  // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(socket_manager_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
    std::cerr << "setsockopt failed\n";
    return;
  }
  
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(6379);
  
  if (bind(socket_manager_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    std::cerr << "Failed to bind to port 6379\n";
    return;
  }
}

void SocketManager::close_socket_manager() {
  close(socket_manager_fd);
  std::cout << "Socket manager connection closed\n"; 
}

int SocketManager::create_new_connection() {
  int socket_fd;

  int connection_backlog = 5;
  if (listen(socket_manager_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return -1;
  }

  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);

  std::cout << "Waiting for a client to connect...\n";

  socket_fd = accept(socket_manager_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
  std::cout << "Client connected to socket " << socket_fd << "\n";

  return socket_fd;
}



ssize_t SocketManager::recv_msg(const int & socket_fd, char * msg, const int length){
  return read(socket_fd, msg, length);
}

ssize_t SocketManager::send_msg(const int & socket_fd, const char * msg) {
  return send(socket_fd, msg, strlen(msg), 0);
}