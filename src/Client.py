import socket

def main():
    # Create a socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Set up the server address and port
    server_address = ('127.0.0.1', 6379)  # Replace with the actual server IP and port

    # Connect to the server
    client_socket.connect(server_address)

    # Message to send
    message = "ping\nping"

    # Send the message to the server
    client_socket.sendall(message.encode())


    print("Message sent successfully")

    # Wait for the response from the server
    response = client_socket.recv(1024).decode()

    # Print the server's response
    print("Received response from server:", response)

    # Close the socket
    client_socket.close()

if __name__ == "__main__":
    main()
