#include <QtGui/QApplication>
#include "femainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FEMainWindow w;
    w.show();

    return a.exec();
}
