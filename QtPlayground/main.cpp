#include "qtplayground.h"
#include "CollapsibleHeader/collapsible_header.h"
#include <QtWidgets/QApplication>
#include <QtCore/QLibraryInfo>

#include <QtWidgets/QLineEdit>
#include <QtGui/QDoubleValidator>
int main(int argc, char *argv[])
{    
    //QCoreApplication::addLibraryPath(QLibraryInfo::path(QLibraryInfo::PluginsPath));
    QApplication a(argc, argv);
    QtPlayground w;
    w.show();

    CollapsibleHeader header;

    for (int i = 0; i < 5; ++i) {
       // header.insertItem(i, new QLineEdit("goodman"), QString::number(i) + QString("line"));
    }
    header.show();
    return a.exec();
}
