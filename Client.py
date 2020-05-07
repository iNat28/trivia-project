import socket
from bson import BSON
import json
SERVER_IP = "localhost"
SERVER_PORT = 40200
LOGIN_CODE = 10
SIGNUP_CODE = 11
ERROR_CODE = 0

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def serialize_msg(json_msg):
    encoded_msg = BSON.encode(json_msg)
    return encoded_msg


def deserialize_msg(encoded_msg):
    json_msg = BSON.decode(encoded_msg)
    return json_msg


def send_request(code, json_msg):
    sock.sendall(bytes([code]))
    sock.sendall(len(serialize_msg(json_msg)).to_bytes(4, byteorder="little"))
    sock.sendall(serialize_msg(json_msg))


def recieve_response():
    response_code = sock.recv(1).decode()
    response_length_inbytes = sock.recv(4)
    response_length = int.from_bytes(response_length_inbytes, byteorder='big')
    response = sock.recv(response_length).decode()
    json_msg = deserialize_msg(response)
    if response_code == ERROR_CODE:
        return json_msg["message"]
    else:
        return json_msg["status"]


def main():
    try:
        sock.connect((SERVER_IP, SERVER_PORT))

        json_msg = {}
        json_msg["username"] = "Yonatan"
        json_msg["password"] = "325709frhpQCK"

        send_request(LOGIN_CODE, json_msg)

        print(recieve_response())

        sock.close()
    except Exception as e:
        print("Error while trying to connect to server - " + str(e))

if __name__ == '__main__':
    main()
