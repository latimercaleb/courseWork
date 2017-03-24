#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = window.width() * window.height();

    window.setWindowTitle("OpenGL with Qt");

    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        window.show();
    else
        window.showMaximized();
    return app.exec();
}
