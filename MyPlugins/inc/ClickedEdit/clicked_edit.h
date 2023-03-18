#pragma once

#include <QtWidgets/QLineEdit>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT ClickedEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ClickedEdit(QWidget* parent = nullptr);
    explicit ClickedEdit(const QString&, QWidget* parent = nullptr);
    ~ClickedEdit() = default;

protected:    
    void mouseReleaseEvent(QMouseEvent* event) override;

signals:
    void Clicked();    
};
