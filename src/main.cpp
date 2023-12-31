#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "Server.h"
#include "SocketManager.h"

/*
TODO:
- improve recv_msg logic
- implement optional for DB?
*/

int main(int argc, char **argv) {
  Server server;
  server.serve();
}