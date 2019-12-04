import socket
import sys

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

server_address = ('127.0.0.3',8888)
print ('Il server sta partendo con indirizzo e porta')
sock.bind(server_address)

sock.listen(2)
clients = []

while True:
    print("In attesa di connessioni")
    connection, client_address = sock.accept()
    try:
        print('connessione da,')

        while True:
            data = connection.recv(1024)
            print('Dati ricevuti:{}'.format(data))
            if data:
                print('rimando al client')
                connection.sendall(data)
            else:
                print('nessun dato')
                break
    finally:
        connection.close()