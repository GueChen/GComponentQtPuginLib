#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtplayground.h"

class QtPlayground : public QMainWindow
{
    Q_OBJECT

public:
    QtPlayground(QWidget *parent = nullptr);
    ~QtPlayground();

private:
    Ui::QtPlaygroundClass ui;
};
