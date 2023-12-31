#include <string>
#include <cstring>
#include "Service.h"
#include "SocketManager.h"

void Service::dispatcher(SocketManager & socket_manager, const int & socket_fd, char * msg) {
    if (is_pong_service(msg)) {
        pong_service(socket_manager, socket_fd);
    }
}

bool Service::is_pong_service(char * msg) {
    const char * PING_MSG = "ping";

    char * i;

    for (i = msg; * i != '\0'; i++) {
        if (strncmp(i, PING_MSG, strlen(PING_MSG)) == 0) {
            return true;
        }
    }

    return false;
}

void Service::pong_service(SocketManager & socket_manager, const int & socket_fd) {
    const char * PONG_MSG = "+PONG\r\n";
    socket_manager.send_msg(socket_fd, PONG_MSG);
}