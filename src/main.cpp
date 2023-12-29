#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "SocketManager.h"

int main(int argc, char **argv) {
  Server server;
  server.run();
}