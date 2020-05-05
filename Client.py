import socket

SERVER_IP = "localhost"
SERVER_PORT = 40200


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((SERVER_IP, SERVER_PORT))
        server_msg = sock.recv(5).decode()
        if server_msg == "Hello":
            sock.sendall("Hello".encode())
        sock.close()
    except Exception as e:
        print("Error while trying to connect to server - " + str(e))

if __name__ == '__main__':
    main()
