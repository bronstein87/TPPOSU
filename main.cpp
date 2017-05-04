#include <QApplication>
#include "mainwindow.h"
#include "connectiondialog.h"

qint32 main(qint32 argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    qApp->addLibraryPath("plugins");
    QApplication a(argc, argv);
//    QApplication::setAttribute(Qt::AA_Use96Dpi);
//    QFont font = qApp->font();
//    font.setPixelSize(11);
    MainWindow f;
    f.show();

    return a.exec();
}
