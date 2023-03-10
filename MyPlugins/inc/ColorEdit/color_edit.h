#ifndef __COLOR_EDITOR_H
#define __COLOR_EDITOR_H

#include <QtWidgets/QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ColorEdit;
}
QT_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT ColorEdit : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color MEMBER color_ NOTIFY ColorChanged READ GetColor WRITE SetColor)
public:
    explicit ColorEdit(QWidget *parent = nullptr, QColor color = Qt::blue);
    ~ColorEdit();

    inline QColor GetColor  ()  const             { return color_; }
    void          SetColor  (const QColor& color);

private:
    void          SetRed    (float red_val);
    void          SetGreen  (float green_val);
    void          SetBlue   (float blue_val);
    void          SetAlpha  (float alpha_val);
signals:
    void ColorChanged(const QColor& color);

private:
    QColor            color_;
    Ui::ColorEdit*    ui_ptr_;
};


#endif // !__COLOR_EDITOR_H