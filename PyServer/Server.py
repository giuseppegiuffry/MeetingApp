import socket
import sys
from threading import Thread
import json
import sqlite3


def accept_connections():
    while True:
        connection, client_address = sock.accept()
        print("\nConnesso con " + client_address[0] + ":" + str(client_address[1]))
        clients[connection.fileno()] = connection
        # addresses[connection] = client_address
        Thread(target=clientThread,args=(connection,client_address,)).start()


def clientThread(connection,client_address):
    while True:
        data = connection.recv(1024)
        encode = json.dumps(data)
        jdata = json.loads(encode.decode("utf-8"))
        # print('\nMessaggio ricevuto: \n{}'.format(data.decode("utf-8")))
        if data:
            print('\nMessaggio ricevuto: \n{}'.format(data.decode("utf-8")))
            print('\nRimando al client')
            for client in clients.values():
                if (client != connection):
                    client.sendall(data)
        else:
            print('\nClient disconnesso')
            del clients[connection.fileno()]
            connection.close()
            # del addresses[connection]
            break

    connection.close()

def broadcast(messaggio):
    for sock in clients:
        sock.sendall(messaggio)


sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ('127.0.0.1', 8888)
sock.bind(server_address)

clients = {}
addresses = {}

if __name__ == "__main__":
    db = sqlite3.connect('database.db')
    c = db.cursor()
    sock.listen(5)
    print("In attesa di connessioni...")
    thread_connessioni = Thread(target=accept_connections)
    thread_connessioni.start()
    thread_connessioni.join()
    sock.close()