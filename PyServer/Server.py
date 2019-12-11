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
        db = sqlite3.connect('database.db')
        c = db.cursor()
        # print('\nMessaggio ricevuto: \n{}'.format(data.decode("utf-8")))
        if data:
            temp = data.decode("utf-8")
            temp = temp[4:]
            jdata = json.loads(temp)
            print('\nMessaggio ricevuto: \n{}'.format(data.decode("utf-8")))
            if "login" in jdata:
                account = []
                account.append(jdata.get("name"))
                account.append(jdata.get("password"))
                c.execute('SELECT * FROM account WHERE username = ? AND password = ?',account)
                result = c.fetchone() #prendo il risultato del fetch e vedo se non è nullo 

                if result:
                    print('\nUtente loggato')
                    #connection.sendall(validation_granted.encode()) queste due rompono la comunicazione!
                else:
                    print('\nCredenziali errate')
                    #connection.sendall(validation_refused.encode()) queste due rompono la comunicazione!

            elif "msg" in jdata:
                for client in clients.values():
                    if (client != connection):
                        client.sendall(data)

            elif "bio" in jdata:
                print("\nSalvo utente nel database")
                user = []
                account = []
                user.append(jdata.get("name"))
                user.append(jdata.get("surname"))
                user.append(jdata.get("sex"))
                user.append(jdata.get("interested"))
                user.append(jdata.get("bio"))
                account.append(jdata.get("nickname"))
                account.append(jdata.get("password"))
                c.execute('INSERT INTO user VALUES (?,?,?,?,?)', user)
                c.execute('INSERT INTO account VALUES(?,?)', account)
                db.commit()
            else:
                print("\nMessaggio non riconosciuto")

        else:
            print('\nClient disconnesso')
            del clients[connection.fileno()]
            connection.close()
            # del addresses[connection]
            break

    connection.close()


sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ('127.0.0.2', 8888)
sock.bind(server_address)

clients = {}
addresses = {}

validation_granted = '{"granted":"granted"}'
validation_refused = '{"granted":"refused"}'

if __name__ == "__main__":
    sock.listen(5)
    print("In attesa di connessioni...")
    thread_connessioni = Thread(target=accept_connections)
    thread_connessioni.start()
    thread_connessioni.join()
    sock.close()