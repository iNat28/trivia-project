import socket
from bson import BSON
import json
SERVER_IP = "localhost"
SERVER_PORT = 40200
LOGIN_CODE = 10
SIGNUP_CODE = 11

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def serialize_msg(json_msg):
    encoded_msg = BSON.encode(json_msg)
    return encoded_msg


def deserialize_msg(encoded_msg):
    json_msg = BSON.decode(encoded_msg)
    return json_msg


def send_request(code, json_msg):
    sock.sendall(code.encode())
    sock.sendall(len(serialize_msg(json_msg)).encode())
    sock.sendall(serialize_msg(json_msg).encode())


def main():
    try:
        sock.connect((SERVER_IP, SERVER_PORT))
        server_msg = sock.recv(5).decode()
        if server_msg == "Hello":
            sock.sendall("Hello".encode())
        json_msg = {}
        json_msg["username"] = "tani"
        json_msg["password"] = "12345"
        send_request(LOGIN_CODE, json_msg)

        sock.close()
    except Exception as e:
        print("Error while trying to connect to server - " + str(e))

if __name__ == '__main__':
    main()
