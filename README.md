# MyDB

MyDB is a Database Management System, designed based on Redis. It supports basic Redis commands such as GET and SET, follows Redis RESP protocol for request and response and saves and loads data locally using .rds formatting.

## Features

- **Respond to the PING command:** The PING command is a simple way to check if the server is running and responding to commands. When the server receives a PING command, it should respond with a PONG message.

- **Respond to the ECHO command:** The ECHO command is used to test the connection between the client and server. When the server receives an ECHO command, it should respond with the same message that was sent by the client.

- **Support the SET and GET commands:** The SET command is used to set the value of a key in the Redis database, while the GET command is used to retrieve the value of a key. In this project, you'll implement a simple version of these commands that only supports setting and getting string values.

- **Support setting a key with an expiry:** In addition to setting the value of a key, Redis also supports setting an expiry time for the key. When the expiry time is reached, the key is automatically deleted from the database. In this project, you'll add support for setting an expiry time in milliseconds using the "PX" argument to the SET command.

- **Support reading a key from an RDB file:** Redis uses RDB files for persistence, which are binary files that contain a snapshot of the Redis database. In this project, you'll add support for reading a single key from an RDB file.

- **Support reading multiple keys from an RDB file:** Finally, you'll add support for reading multiple keys from an RDB file. The tester will create an RDB file with multiple keys and execute your program, sending a "keys *" command to your server. Your server should respond with an array of all the keys in the database.

## How to run?

1. Clone the repository to your local machine

2. Navigate to the project directory in your terminal

3. Run the `spawn_redis_server.sh` script to start the Redis server on port 6379. This script takes two arguments: `--dir` and `--dbfilename`. The `--dir` argument specifies the directory where RDB files are stored, while the `--dbfilename` argument specifies the name of the RDB file. For example, to start the server with RDB files stored in the `/tmp/redis-files` directory and a filename of `dump.rdb`, run the following command:

```
./spawn_redis_server.sh --dir /tmp/redis-files --dbfilename dump.rdb
```

The server will run on port 6379!