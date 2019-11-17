#include <QApplication>
#include "chatwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();



    //ChatWindow chatWin;
    //chatWin.show();

    return a.exec();
}
