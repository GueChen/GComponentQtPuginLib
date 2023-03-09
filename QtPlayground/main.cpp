#include "qtplayground.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLibraryInfo>
int main(int argc, char *argv[])
{
    //QCoreApplication::addLibraryPath(QLibraryInfo::path(QLibraryInfo::PluginsPath));
    QApplication a(argc, argv);
    QtPlayground w;
    w.show();
    return a.exec();
}
