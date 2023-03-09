#ifndef __COLOR_CANVAS_H
#define __COLOR_CANVAS_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QColorDialog>
#include <QtUiPlugin/QDesignerExportWidget>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class DisplayColor;
}
QT_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT ColorCanvas : public QLabel
{
    Q_OBJECT

    Q_PROPERTY(QColor color MEMBER color_ NOTIFY ColorChanged)
public:
    explicit ColorCanvas(QWidget *parent = nullptr, QColor color = Qt::blue);


protected:
    void mouseReleaseEvent(QMouseEvent* event)    override;
    void resizeEvent(QResizeEvent* event)         override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void ColorChange(const QColor& color);

signals:
    void ColorChanged(const QColor& color);

private:
    QColor            color_;
    QFrame            frame_;
    QLabel            color_disply_text_;
    QColorDialog      selector_;
    Ui::DisplayColor* display_ptr_;
};


#endif // !__COLOR_CANVAS_H