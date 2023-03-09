#include "dragedit.h"

#include <QtGui/QMouseEvent>

DragEdit::DragEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setCursor(Qt::SizeVerCursor);
}

void DragEdit::mouseMoveEvent(QMouseEvent* event)
{

    if (is_draged_ && (event->buttons() & Qt::LeftButton)) {
        QPoint cur_pos = event->pos();
        setText(QString::number(cur_pos.x()) + ", " + QString::number(cur_pos.y()));        
    }
}

void DragEdit::mousePressEvent(QMouseEvent* event)
{
    if (!is_draged_ && (event->buttons() & Qt::LeftButton)) {
        setMouseTracking(true);
        last_pos_  = event->pos();
        is_draged_ = true;
#ifdef _TRACKING_DBG
        setText("tracking...");
#endif
    }
}

void DragEdit::mouseReleaseEvent(QMouseEvent* event)
{    

    if (is_draged_ && !(event->buttons() & Qt::LeftButton)) {
        setMouseTracking(false);
        is_draged_ = false;
#ifdef _TRACKING_DBG
        setText("un tracking...");
#endif
    }
}
