cmake_minimum_required(VERSION 3.13)
project(redis-starter-cpp)
set(CMAKE_CXX_STANDARD 20) # Enable the C++20 standard

set(SOURCE_FILES 
    src/main.cpp
    src/SocketManager.cpp
    src/Server.cpp
    src/Service.cpp
    src/Database.cpp
    src/Utils.cpp
    src/ArgsParser.cpp
    src/Config.cpp
    src/FileManagement.cpp
    )

add_executable(server ${SOURCE_FILES})

# Link the pthread library
find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)