import socket

SERVER_IP = "localhost"
SERVER_PORT = 40200

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((SERVER_IP, SERVER_PORT))

        user_input = input()
        sock.sendall(user_input.encode())
        print(sock.recv(1024).decode())
        sock.close()
    except:
        print("Couldn't connect to server")

if __name__ == '__main__':
    main()
