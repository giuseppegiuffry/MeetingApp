import socket
import sys
from _thread import *

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

server_address = ('127.0.0.1', 8888)
print ('Il server sta partendo con indirizzo e porta')
sock.bind(server_address)

sock.listen(5)

print("In attesa di connessioni...")

clients = []

def clientThread(connection):
    while True:
        data = connection.recv(1024)
        # print('\nMessaggio ricevuto: \n{}'.format(data.decode("utf-8")))
        if data:
            print('\nMessaggio ricevuto: \n{}'.format(data.decode("utf-8")))
            print('\nRimando al client')
            connection.sendall(data)
        else:
            print('\nNessun messaggio ricevuto')
            print("Il client " + client_address[0] + ":" + str(client_address[1]) + " è offline")
            break

    connection.close()
    
    
while True:
    connection, client_address = sock.accept()
    
    print("\nConnesso con " + client_address[0] + ":" + str(client_address[1]))
    start_new_thread(clientThread, (connection,))
    

sock.close()