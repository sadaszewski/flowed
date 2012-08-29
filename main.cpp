#include <QtGui/QApplication>
#include <QSettings>
#include <QDialog>

#include "femainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FEMainWindow w;

    QSettings s("algoholic.eu", "flowed");
    if (!s.value("license_accepted", false).toBool()) {
        if (w.showLicense() == QDialog::Rejected) {
            return 0;
        }
    }

    w.show();

    return a.exec();
}
