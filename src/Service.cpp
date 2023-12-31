#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
#include <iostream>
#include <unistd.h>
#include "Service.h"
#include "SocketManager.h"
#include "Database.h"

void Service::dispatcher(SocketManager & socket_manager, const int & socket_fd, const std::string & input, Database & database) {
  std::vector<std::string> deserialized_input = deserialize(input);
  std::string command = extract_command(deserialized_input);

  std::cout << "Command: " << command << std::endl;

  if (is_pong_service(command)) {
    pong_service(socket_manager, socket_fd);
  } else if (is_echo_service(command)) {
    echo_service(socket_manager, socket_fd, deserialized_input);
  } else if (is_set_service(command)) {
    set_service(socket_manager, socket_fd, deserialized_input, database);
  } else if (is_get_service(command)) {
    get_service(socket_manager, socket_fd, deserialized_input, database);
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
  std::string PONG_MSG = "+PONG\r\n";
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
  socket_manager.send_msg(socket_fd, msg);
}

bool Service::is_set_service(const std::string & command) {
  return command == "set";
}

void Service::set_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Database & database) {
  if (deserialized_input.size() < 7) {
    return;
  }
  std::string key = deserialized_input[4], value = deserialized_input[6];
  database.set(key, value);

  std::string resp = "+OK\r\n";
  socket_manager.send_msg(socket_fd, resp);
}

bool Service::is_get_service(const std::string & command) {
  return command == "get";
}

void Service::get_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Database & database) {
  if (deserialized_input.size() < 5) {
    return;
  }
  std::string key = deserialized_input[4];
  std::string value = database.get(key);

  std::string resp = value != "" ? "+" + value + "\r\n" : "+(nil)\r\n";
  socket_manager.send_msg(socket_fd, resp);
}

