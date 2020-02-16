# MeetingApp
## Advanced Programming Languages
### Capodicasa Francesco - Giuffrida Giuseppe
#### Deployment Server
Per effettuare il deploy del server scritto in Python, installare la suite di librerie NLTK con il comando:

```
pip install --user -U nltk
```

Utilizzando l'intreprete Python, digitare da riga di comando:

```
import nltk
nltk.download(‘popular’)
```

A questo punto, spostarsi all'interno della directory PyServer e, per avviare il server, eseguire da riga di comando:

```
python Server.py
```

#### Deployment Client
Per eseguire il client, qualora non fosse presente, è necessario installare [Qt5](https://doc.qt.io/qt-5/gettingstarted.html).
Si consiglia di utilizzare questo link, in quanto l'installazione dell'ambiente potrebbe differire in alcuni passaggi, a
seconda del sistema operativo su cui si sta eseguendo.
All'interno del programma, aprire il progetto presente nella directory QTClient e chiamato MeetingAppClient.pro

Se si volesse invece eseguire il client da terminale, compilando il codice sorgente e creando un file eseguibile, senza dover installare l'ambiente, si può fare riferimento a questa [guida](https://vitux.com/compiling-your-first-qt-program-in-ubuntu/), che va per bene anche per altri sistemi operativi, oltre a Ubuntu. 
Nello specifico, i passi da seguire sono gli step 5, 6 e 7 della precedente guida e devono essere eseguiti tutti all'interno della directory QTClient:

```
cd QTClient
qmake MeetingAppClient.pro
make
./MeetingAppClient
```



