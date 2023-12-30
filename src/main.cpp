#include <iostream>
#include <unistd.h>
#include "Service.h"
#include "SocketManager.h"

/*
TODO:
- fix recv_msg logic
- tidy up main server logic
*/

int main(int argc, char **argv) {
  Service service;
  service.serve();
}