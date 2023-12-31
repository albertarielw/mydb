#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <unordered_map>
#include <chrono>
#include "Database.h"
#include "Utils.h"

void Database::set(const std::string & key, const std::string & value) {
    database[key] = value;

    for (auto &[k, v]: database) {
        std::cout << "key: " << k << "value: " << v << std::endl;
    }

    if (expiry.find(key) != expiry.end()) {
        expiry.erase(key);
    }
}

void Database::set_with_expiry(const std::string & key, const std::string & value, const int & expiry_duration_in_milisecond) {
    database[key] = value;
    expiry[key] = get_expiry_timestamp(expiry_duration_in_milisecond);

    for (auto &[k, v]: database) {
        std::cout << "key: " << k << "value: " << v << std::endl;
    }
}

std::string Database::get(const std::string & key) {
    for (auto &[k, v]: database) {
        std::cout << "key: " << k << " value: " << v << std::endl;
    }

    if (database.find(key) == database.end()) {
        return "";
    }

    std::cout << "Current timestamp: " << convert_to_unix_timestamp(get_current_timestamp()) << std::endl;
    if (expiry.find(key) != expiry.end()) {
        std::cout << "Expiry timestamp: " << convert_to_unix_timestamp(expiry[key]) << std::endl;
    }

    if (expiry.find(key) != expiry.end() && get_current_timestamp() > expiry[key]) {
        return "";
    }

    return database[key];
}

void Database::update(std::unordered_map<std::string, std::string> & new_database, std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> & new_expiry) {
    for (auto &[key, value]: new_database) {
        database[key] = value;
    }

    for (auto &[key, value]: new_expiry) {
        expiry[key] = value;
    }
}

std::vector<std::string> Database::get_all_keys() {
    std::vector<std::string> all_keys;
    for (auto &[key, value]: database) {
        all_keys.push_back(key);
    }
    return all_keys;
}