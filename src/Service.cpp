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
  } else if (is_echo_service(command)) {
    echo_service(socket_manager, socket_fd, deserialized_input);
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

bool Service::is_echo_service(const std::string & command) {
  return command == "echo";
}

void Service::echo_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input) {
  if (deserialized_input.size() < 5) {
    return;
  }
  std::string msg = "+" + deserialized_input[4] + "\r\n";
  std::cout << "echo: " << msg << std::endl;
  socket_manager.send_msg(socket_fd, msg.c_str());
}
