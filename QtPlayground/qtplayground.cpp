#include "qtplayground.h"

QtPlayground::QtPlayground(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.selector->AddItems({
       "Good", "Basdd", "control", "Learn"
        });
}

QtPlayground::~QtPlayground()
{
   
}
