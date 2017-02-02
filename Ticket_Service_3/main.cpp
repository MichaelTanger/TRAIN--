#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool is_again=false;
    do
    {
        MainWindow w;
        w.show();
        a.exec();
        is_again=w.getIs_again();
    }while(is_again);


    return 0;
}
