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
All'interno del programma, aprire il progetto presente nella directory QTClient e chiamato Prova.pro

