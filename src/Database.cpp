#include <string>
#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include "Database.h"

void Database::set(const std::string & key, const std::string & value) {
    database[key] = value;

    for (auto &[k, v]: database) {
        std::cout << "key: " << k << "value: " << v << std::endl;
    }
}

std::string Database::get(const std::string & key) {
    for (auto &[k, v]: database) {
        std::cout << "key: " << k << "value: " << v << std::endl;
    }

    if (database.find(key) == database.end()) {
        return "";
    }

    return database[key];
}