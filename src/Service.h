#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <unistd.h>
#include "Service.h"
#include "SocketManager.h"

class Service {
public:
  void serve();

private:
  SocketManager socket_manager;
};

#endif
