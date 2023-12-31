#include <string>
#include <cstring>
#include "Service.h"
#include "SocketManager.h"

void Service::pong_service(SocketManager & socket_manager, const int & socket_fd, char * msg) {
    const char * PING_MSG = "ping";
    const char * PONG_MSG = "+PONG\r\n";

    char *t; 

    socket_manager.send_msg(socket_fd, PONG_MSG);
    
    // for (t = msg; *t != '\0'; t++) {
    //   if (*t == 'p' && strncmp(t, PING_MSG, strlen(PING_MSG)) == 0) {
        
    //   }
    // }
}