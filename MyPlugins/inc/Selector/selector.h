#pragma once

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialog>
#include <QtUiPlugin/QDesignerExportWidget>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui{ class ListSelectorDialog; }
QT_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT GSelector : public QLineEdit
{
    Q_OBJECT

public:
    explicit GSelector(QWidget* parent = nullptr, const QString& value = "null", const QStringList & values = {});
    ~GSelector();

    void SetList   (const QStringList& values);

    void AddItems  (const QStringList& values);
    void AddItem   (const QString& value);

    void RemoveItem(const QString& value);
    void ClearItems();


    void SetCurrent(const QString& value);
    void SetDialogTitle(const QString& dialog_title);

protected:    
    void mouseReleaseEvent(QMouseEvent* event) override;

private:    
    QDialog                                 list_dialog_;
    std::unique_ptr<Ui::ListSelectorDialog> dialog_ui_ptr_;
};
