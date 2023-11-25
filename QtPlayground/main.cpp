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
    header.SetPageContent(new QLineEdit("This is Collapsible header"));
    header.show();
    return a.exec();
}
