#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <vector>
#include <functional>
#include "Server.h"
#include "Service.h"
#include "SocketManager.h"
#include "Config.h"
#include "FileManagement.h"

Server::Server(Config & config): config(config), file_management(config) {}

void Server::serve() {
  setup_server();

  std::vector<std::thread> all_threads;

  while (true) {
    int socket_fd = socket_manager.create_new_connection();
    std::thread service_thread(std::bind(&Server::main_service, this, socket_fd));
    all_threads.emplace_back(std::move(service_thread));
  }

  for (int i = 0; i < all_threads.size(); ++i) {
    if (all_threads[i].joinable()) {
      all_threads[i].join();
    }
  }
  
  close_server();
}

void Server::setup_server() {
  socket_manager.setup_socket_manager();
}

void Server::close_server() {
  socket_manager.close_socket_manager();
}

void Server::main_service(int socket_fd) {
  while (true) {
    const int MSG_SIZE_MAX = 1024;
    char msg[MSG_SIZE_MAX] = {};
    ssize_t bytes_recv = socket_manager.recv_msg(socket_fd, msg, MSG_SIZE_MAX);

    if (bytes_recv <= 0) {
      std::cout << "Client disconnected\n";
      if (socket_fd != -1) {
        close(socket_fd);
      }
      break;
    }

    std::cout << "Received msg from " << socket_fd << " : " << msg << std::endl;

    Service service;
    std::string input(msg);
    service.dispatcher(socket_manager, socket_fd, input, database, config, file_management);
  }
}