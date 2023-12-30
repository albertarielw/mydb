#include <iostream>
#include <unistd.h>
#include <thread>
#include "Server.h"

/*
TODO:
- fix recv_msg logic
- tidy up main server logic
*/

int main(int argc, char **argv) {
  Server server;

  server.serve();
}