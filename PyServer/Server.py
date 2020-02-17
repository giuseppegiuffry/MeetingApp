import socket
import sys
from threading import Thread
import json
import sqlite3
import difflib
import nltk
from nltk.stem.snowball import SnowballStemmer
from nltk.tokenize import sent_tokenize, word_tokenize


def accept_connections():
    while True:
        connection, client_address = sock.accept()
        print("\nConnesso con " + client_address[0] + ":" + str(client_address[1]))
        clients[connection.fileno()] = connection
        clients_ids[connection.fileno()] = 0
        Thread(target=clientThread,args=(connection,client_address,)).start()


def clientThread(connection,client_address):
    while True:
        data = connection.recv(2048)
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
                result = c.fetchone()

                if result:
                    print(result)
                    user_id = result[2]
                    clients_ids[connection.fileno()] = user_id
                    c.execute('SELECT bio,sex,interested FROM user WHERE id = "%s"' % user_id)
                    result = c.fetchone()
                    user_bio = result[0]
                    user_sex = result[1]
                    user_interest = result[2]
                    print('\nUtente loggato')
                    connection.sendall(data)
                else:
                    print('\nCredenziali errate')

            elif "msg" in jdata:
                for client in clients.values():
                    if (client != connection):
                        other_id = clients_ids[client.fileno()]
                        c.execute('SELECT bio,sex,interested FROM user WHERE id = "%s"' % other_id)
                        result = c.fetchone()
                        other_bio = result[0]
                        other_sex = result[1]
                        other_interest = result[2]
                        output = matching(user_bio,user_sex,user_interest,other_bio,other_sex,other_interest)
                        print("Valore di match: " + str(output))
                        if (output >= 60):
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

def matching(user_bio,user_sex,user_interest,other_bio,other_sex,other_interest):
    print("\nEntro in matching")
    i = 0
    totale = 0
    if((user_sex == other_interest) and (user_interest == other_sex)):
        user_words=word_tokenize(user_bio)
        other_words=word_tokenize(other_bio)
        user_stemmed = []
        other_stemmed = []
        for word in user_words:
            user_stemmed.append(stemmer.stem(word))
        for word in other_words:
            other_stemmed.append(stemmer.stem(word))
        print(user_stemmed)
        print(other_stemmed)
        for a in user_stemmed:
            for b in other_stemmed:
                parziale = int(difflib.SequenceMatcher(None, a, b).ratio()*100)
                if (parziale == 100):
                    break
            i = i + 1
            totale = totale + parziale
        return (totale/i)
    else:
        return 0


sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ('127.0.0.3', 8888)
sock.bind(server_address)

clients = {}
clients_ids = {}
output = 0
stemmer = SnowballStemmer("italian")

if __name__ == "__main__":
    sock.listen(5)
    print("In attesa di connessioni...")
    thread_connessioni = Thread(target=accept_connections)
    thread_connessioni.start()
    thread_connessioni.join()
    sock.close()