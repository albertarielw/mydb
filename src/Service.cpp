#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
#include <iostream>
#include <unistd.h>
#include "Service.h"
#include "SocketManager.h"
#include "Database.h"
#include "Utils.h"
#include "Config.h"
#include "FileManagement.h"

void Service::dispatcher(SocketManager & socket_manager, const int & socket_fd, const std::string & input, Database & database, Config & config, FileManagement & file_management) {
  std::vector<std::string> deserialized_input = deserialize(input);
  std::string command = extract_command(deserialized_input);

  std::cout << "Command: " << command << std::endl;

  if (is_pong_service(command)) {
    pong_service(socket_manager, socket_fd);
  } else if (is_echo_service(command)) {
    echo_service(socket_manager, socket_fd, deserialized_input);
  } else if (is_set_service(command)) {
    if (is_set_service_with_expiry(command, deserialized_input)) {
      set_service_with_expiry(socket_manager, socket_fd, deserialized_input, database);
      return;
    } 
    set_service(socket_manager, socket_fd, deserialized_input, database);
  } else if (is_get_service(command)) {
    get_service(socket_manager, socket_fd, deserialized_input, database);
  } else if (is_config_service(command)) {
    if (is_config_get_service(command, deserialized_input)) {
      config_get_service(socket_manager, socket_fd, deserialized_input, config);
    }
  } else if (is_keys_service(command)) {
    std::cout << "is keys service" << std::endl;
    if (is_get_all_keys_service(command, deserialized_input)) {
      std::cout << "is get all keys service" << std::endl;
      get_all_keys_service(socket_manager, socket_fd, file_management);
    }
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

void Service::encode_bulk_string(std::string &resp, const std::string &str) {
  resp += "$" + std::to_string(str.length()) + "\r\n" + str + "\r\n";
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

  std::string resp = value != "" ? "+" + value + "\r\n" : "$-1\r\n";
  socket_manager.send_msg(socket_fd, resp);
}

bool Service::is_set_service_with_expiry(const std::string & command, const std::vector<std::string> & deserialized_input) {
  return command == "set" && deserialized_input.size() >= 11 && convert_to_lowercase(deserialized_input[8]) == "px";
}

void Service::set_service_with_expiry(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Database & database) {
  if (deserialized_input.size() < 11) {
    return;
  }
  std::string key = deserialized_input[4], value = deserialized_input[6];

   const int expiry_duration_in_milisecond = std::stoi(deserialized_input[10]);
  database.set_with_expiry(key, value, expiry_duration_in_milisecond);

  std::string resp = "+OK\r\n";
  socket_manager.send_msg(socket_fd, resp);
}

bool Service::is_config_service(const std::string & command) {
  return command == "config";
}

bool Service::is_config_get_service(const std::string & command, const std::vector<std::string> & deserialized_input) {
  return command == "config" && deserialized_input.size() >= 7 && convert_to_lowercase(deserialized_input[4]) == "get";
}

std::string Service::encode_config_get_response(const std::string &key, const std::string &value) {
  std::string resp = "*2\r\n";
  encode_bulk_string(resp, key);
  encode_bulk_string(resp, value);
  return resp;
}

void Service::config_get_service(SocketManager & socket_manager, const int & socket_fd, const std::vector<std::string> & deserialized_input, Config & config) {
  if (deserialized_input.size() < 7) {
    return;
  }
  std::string key = deserialized_input[6];

  std::string value = config.get_config(key);

  std::string resp = encode_config_get_response(key, value);

  socket_manager.send_msg(socket_fd, resp);
}

bool Service::is_keys_service(const std::string & command) {
  return command == "keys";
}

bool Service::is_get_all_keys_service(const std::string & command, const std::vector<std::string> & deserialized_input) {
  return command == "keys" && deserialized_input.size() >= 5 && deserialized_input[4] == "*";
};

void Service::get_all_keys_service(SocketManager & socket_manager, const int & socket_fd, FileManagement & file_management) {
  std::string resp = "";
  encode_bulk_string(resp, file_management.readFileAndGetKeys());
  resp = "*1\r\n" + resp;
  std::cout << "resp is: " << resp << std::endl;
  socket_manager.send_msg(socket_fd, resp);
};

