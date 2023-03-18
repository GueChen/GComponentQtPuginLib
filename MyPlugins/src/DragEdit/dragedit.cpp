#include "DragEdit/drag_edit.h"

#include <QtGui/QMouseEvent>

#include <cmath>

DragEdit::DragEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setCursor(Qt::SizeVerCursor);
    setText  (QString::number(value_, 10, 2));
    
}

void DragEdit::SetValue(float val) {
    if (value_ != val) {
        value_ = val;
        setText(QString::number(value_, 10, 2));
        emit ValueChanged(val);
    }
}

void DragEdit::mouseMoveEvent(QMouseEvent* event)
{

    if (is_draged_ && (event->buttons() & Qt::LeftButton)) {
        QPoint cur_pos = event->pos();
        QPoint diff    = cur_pos - last_pos_;
        last_pos_      = cur_pos;

        float new_value = value_ + step_ * (diff.x() - diff.y());
        new_value       = std::max(std::min(new_value, max_limit_), min_limit_);
        
        SetValue(new_value);        
#ifdef _TRACKING_DBG
        setText(QString::number(cur_pos.x()) + ", " + QString::number(cur_pos.y()));
#endif
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
