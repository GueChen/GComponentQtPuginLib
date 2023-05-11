#include "qtplayground.h"
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

    QLineEdit lineEdit;
    QDoubleValidator validate;
    validate.setTop(100.0f);
    validate.setBottom(-100.0f);
    validate.setNotation(QDoubleValidator::StandardNotation);
    lineEdit.setValidator(&validate);

    lineEdit.show();
    return a.exec();
}
