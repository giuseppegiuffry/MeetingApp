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
    try:
        while True:
            data = connection.recv(2048)
            db = sqlite3.connect('database.db')
            c = db.cursor()
            if data:
                temp = data.decode("Latin")
                temp = temp[4:]
                jdata = json.loads(temp)
                print('\nMessaggio ricevuto: \n{}'.format(data.decode("Latin")))

                if "login" in jdata:
                    account = []
                    account.append(jdata.get("name"))
                    account.append(jdata.get("password"))
                    c.execute('SELECT * FROM account WHERE username = ? AND password = ?',account)
                    result = c.fetchone()
                    if result:
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

                elif "hello" in jdata:
                    hello_msg = data
                    matched_client = 0
                    max_output = 0
                    black_list = []
                    alredy_matched = False
                    matched = False
                    init_matching(connection,user_bio,user_sex,user_interest,matched_client,
                                  max_output,black_list,alredy_matched,matched,c,hello_msg)

                elif "msg" in jdata:
                    for key in match_pattern.keys():
                        if key == connection:
                            match_pattern[key].sendall(data)
                            matched_client = match_pattern[key]
                        
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

                elif "rematch" in jdata:
                    for key in match_pattern.keys():
                        if key == connection:
                            match_pattern[key].sendall(data)

                    black_listed = False
                    for key in match_pattern.keys():
                        if key == connection:
                            match_pattern.pop(key)
                            match_pattern.pop(matched_client)
                            black_list.append(matched_client)
                            black_listed = True
                            print(match_pattern)
                            break
                    if (black_listed == True):
                        init_matching(connection,user_bio,user_sex,user_interest,matched_client,
                                  max_output,black_list,alredy_matched,matched,c,hello_msg)
                    else:
                        init_matching(connection,user_bio,user_sex,user_interest,matched_client,
                                      max_output,black_list,alredy_matched,matched,c,hello_msg)
                    

                else:
                    print("\nMessaggio non riconosciuto")

            else:
                print('\nClient disconnesso')
                for key in match_pattern.keys():
                    if key == connection:
                        if(matched_client == 0):
                            matched_client = match_pattern[key]
                        match_pattern.pop(key)
                        match_pattern.pop(matched_client)
                        break
                del clients[connection.fileno()]
                del clients_ids[connection.fileno()]
                connection.close()
                break

        connection.close()

    except KeyError as e:
        print("Errore Chiave nel dict")
        print(e)

    except RuntimeError as e:
        print("Errore Runtime")
        print(e)
    except Exception as e:
        print("Qualcosa è andato storto")
        print(e)

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

def init_matching(connection,user_bio,user_sex,user_interest,matched_client,
                                      max_output,black_list,alredy_matched,matched,c,hello_msg):
    for client in clients.values():
        if (client != connection and client not in black_list):
            other_id = clients_ids[client.fileno()]
            c.execute('SELECT bio,sex,interested FROM user WHERE id = "%s"' % other_id)
            result = c.fetchone()
            other_bio = result[0]
            other_sex = result[1]
            other_interest = result[2]
            output = matching(user_bio,user_sex,user_interest,other_bio,other_sex,other_interest)
            print("Valore di match: " + str(output))
            if (max_output < output and output > 60):
                for key in match_pattern.keys():
                    if key == client:
                        alredy_matched = True
                if (alredy_matched == True):
                    print("Questo utente è già occupato")
                else:
                    max_output = output
                    matched_client = client
                    matched = True
    if (matched == True):
        print("matched")
        match_pattern[connection] = matched_client
        match_pattern[matched_client] = connection
        connection.sendall(hello_msg)
        matched_client.sendall(hello_msg)

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ('127.0.0.2', 8888)
sock.bind(server_address)

clients = {}
clients_ids = {}
match_pattern = {}
stemmer = SnowballStemmer("italian")

if __name__ == "__main__":
    sock.listen(5)
    print("In attesa di connessioni...")
    thread_connessioni = Thread(target=accept_connections)
    thread_connessioni.start()
    thread_connessioni.join()
    sock.close()