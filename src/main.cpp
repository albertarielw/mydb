#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include "Server.h"
#include "SocketManager.h"

/*
TODO:
- fix recv_msg logic
- tidy up main server logic
*/

int main(int argc, char **argv) {
  Server server;

  server.serve();

}