import socket
import time

def main():
    # Create a socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Set up the server address and port
    server_address = ('127.0.0.1', 6379)  # Replace with the actual server IP and port

    # Connect to the server
    client_socket.connect(server_address)

    # Message to send
    message = "pingping"

    # Send the message to the server
    client_socket.sendall(message.encode())

    print("Message sent successfully")

    # time.sleep(3)

    response = client_socket.recv(1024).decode()

    # Print the server's response
    print("Received response 1 from server:", response)

    response = client_socket.recv(1024).decode()

    # Print the server's response
    print("Received response 2 from server:", response)

    # Close the socket
    client_socket.close()

if __name__ == "__main__":
    main()
