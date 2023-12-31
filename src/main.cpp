#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "Server.h"
#include "SocketManager.h"

int main(int argc, char **argv) {
  Server server;
  server.serve();
}