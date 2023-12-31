#include <vector>
#include <string>
#include <cstring>
#include "Service.h"
#include "SocketManager.h"

void Service::dispatcher(SocketManager & socket_manager, const int & socket_fd, char * msg) {
  std::string input(msg);
  std::vector<std::string> deserialized_input = deserialize(input);
  std::string command = extract_command(deserialized_input);

  if (is_pong_service(command)) {
    pong_service(socket_manager, socket_fd);
  }
}

std::vector<std::string> Service::deserialize(const std::string & input) {
  std::vector<std::string> output;

  std::string line = "", delimiter = "\r\n";
  int index = 0;
  while (index < input.length()) {
    if (input.substr(index, 2) == delimiter) {
      output.push_back(line);
      line = "";
      index += 2;
    }

    line += input[index];
    ++index;
  }

  return output;
}

std::string Service::extract_command(const std::vector<std::string> & deserialized_input) {
  if (deserialized_input.size() < 3) {
    return "";
  }

  std::string lowercase_command = deserialized_input[2];
  for (auto & c: lowercase_command) {
    c = tolower(c);
  }

  return lowercase_command;
}

bool Service::is_pong_service(const std::string & command) {
  return command == "ping";
}

void Service::pong_service(SocketManager & socket_manager, const int & socket_fd) {
  const char * PONG_MSG = "+PONG\r\n";
  socket_manager.send_msg(socket_fd, PONG_MSG);
}
