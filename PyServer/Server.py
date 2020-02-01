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
        clients_ids[connection.fileno()] = 0
        Thread(target=clientThread,args=(connection,client_address,)).start()


def clientThread(connection,client_address):
    while True:
        data = connection.recv(1024)
        db = sqlite3.connect('database.db')
        c = db.cursor()
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
                print(result)

                if result:
                    user_id = result[2]
                    clients_ids[connection.fileno()] = user_id
                    c.execute('SELECT bio FROM user WHERE id = "%s"' % user_id)
                    result = c.fetchone()
                    user_bio = result[0]
                    print('\nUtente loggato')
                    connection.sendall(data)
                else:
                    print('\nCredenziali errate')

            elif "msg" in jdata:
                for index, client in enumerate(clients.values()):
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
                c.execute('INSERT INTO user(name,surname,sex,interested,bio) VALUES (?,?,?,?,?)', user)
                c.execute('INSERT INTO account(username,password) VALUES(?,?)', account)
                db.commit()
                connection.sendall(data)
            else:
                print("\nMessaggio non riconosciuto")

        else:
            print('\nClient disconnesso')
            del clients[connection.fileno()]
            del clients_ids[connection.fileno()]
            connection.close()
            break

    connection.close()


sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ('127.0.0.2', 8888)
sock.bind(server_address)

clients = {}
clients_ids = {}

if __name__ == "__main__":
    sock.listen(5)
    print("In attesa di connessioni...")
    thread_connessioni = Thread(target=accept_connections)
    thread_connessioni.start()
    thread_connessioni.join()
    sock.close()