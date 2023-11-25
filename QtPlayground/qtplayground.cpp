#include "qtplayground.h"

QtPlayground::QtPlayground(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.selector->AddItems({
       "Good", "Basdd", "control", "Learn"
        });

    ui.widget->SetPageContent(new QLineEdit("LineEdit"));
    ui.widget_2->SetPageContent(new QGroupBox());
    ui.widget_3->SetPageContent(
        new CollapsibleHeader("child1", 
            new CollapsibleHeader("child2", 
                new CollapsibleHeader(
                    "child3", new ColorCanvas)
            )
        )
    );
}

QtPlayground::~QtPlayground()
{
   
}
