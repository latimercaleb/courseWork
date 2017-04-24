#include "qtprogramwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtProgramWin w;
    w.show();
    
    return a.exec();
}
