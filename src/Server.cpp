#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
Bind to port 6379!

1. Socket Creation (socket):

The program begins by creating a socket using socket(AF_INET, SOCK_STREAM, 0). This creates a socket using IPv4 (AF_INET) and TCP (SOCK_STREAM).
The function returns a file descriptor (server_fd) that represents the socket.

2. Set Socket Option (setsockopt):

The setsockopt function is used to set socket options. In this case, it sets the SO_REUSEPORT option to allow the reuse of the port.
This is useful to avoid "Address already in use" errors, especially when restarting the program frequently.

3. Bind to Address and Port (bind):

The program then sets up the server address structure (server_addr) with the specified IPv4 address (INADDR_ANY) and port number (6379).
The bind function associates the socket with the address and port specified in server_addr.

4. Listen for Connections (listen):

The listen function puts the server socket in listening mode, with a maximum backlog of pending connections specified by connection_backlog (in this case, 5).

5. Accept a Connection (accept):

The program then waits for a client to connect using the accept function. This is a blocking call that returns a new file descriptor for the accepted connection.
The client's address information is stored in client_addr.

6. Logging and Cleanup:

The program prints messages to indicate the progress ("Waiting for a client to connect..." and "Client connected").
Finally, the server socket is closed using close(server_fd).

*/

int main(int argc, char **argv) {
  std::cout << "Logs:\n";

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
   std::cerr << "Failed to create server socket\n";
   return 1;
  }
  
  // Since the tester restarts your program quite often, setting REUSE_PORT
  // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
    std::cerr << "setsockopt failed\n";
    return 1;
  }
  
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(6379);
  
  if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    std::cerr << "Failed to bind to port 6379\n";
    return 1;
  }
  
  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }
  
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  
  std::cout << "Waiting for a client to connect...\n";
  
  accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
  std::cout << "Client connected\n";
  
  close(server_fd);

  return 0;
}
