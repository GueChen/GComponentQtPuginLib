#include "SwitchControl/switch_control.h"

#include <QtWidgets/QToolTip>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

SwitchControl::SwitchControl(QWidget *parent) : QWidget(parent)
{
    CHECKED = false;

    QPalette palette(QColor(150,150,150,0));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->resize(baseWidth,baseHeight);
    this->setCursor(Qt::PointingHandCursor);
    buttonPosX = startPos;
    connect(&animationTimer,&QTimer::timeout,this,&SwitchControl::slot_stateChangedAnimation);
}

void
SwitchControl::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QPainterPath path;
    
    painter.setWindow(QRect(-width() / 2,-height() / 2,width(),height()));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    //画slot
    painter.setBrush(slotColor);
    path.addRoundedRect(-baseSlotWidth/2,
                        -baseSlotHeight/2,
                        baseSlotWidth,
                        baseSlotHeight,
                        baseSlotHeight/2,
                        baseSlotHeight/2);
    
    painter.drawPath(path.simplified());
    
    //画button
    painter.setBrush(buttonColor);
    painter.drawEllipse(QPointF(buttonPosX,0),
                        baseButtonDirection/2,
                        baseButtonDirection/2);
}


void
SwitchControl::mouseMoveEvent(QMouseEvent *event)
{
    //QString pos = QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());
    //QToolTip::showText(event->globalPos(), pos, this);
}


QSize
SwitchControl::sizeHint() const
{
    return QSize(baseWidth,baseWidth);
}


void
SwitchControl::mousePressEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if (event->buttons() & Qt::LeftButton) {
            baseButtonDirectionScale = 1.0;
            translate();
            update();
            event->accept();
        } else {
            event->ignore();
        }
    }
}

void 
SwitchControl::mouseReleaseEvent(QMouseEvent *event)
{
    baseButtonDirectionScale = 0.9;
    translate();
    if (isEnabled()) {
        if ((event->type() == QMouseEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton)) {
            event->accept();
            emit sig_buttonMove(CHECKED);
            animationTimer.start(1);
        } else {
            event->ignore();
        }
    }
}


void
SwitchControl::slot_stateChangedAnimation()
{
    //qDebug() << buttonPosX;
    if(!CHECKED)
    {
        if(buttonPosX >= stopPos)
        {
            animationTimer.stop();
            CHECKED = !CHECKED;
            emit stateChanged(CHECKED);
            changeColor(!CHECKED);
            update();
            //qDebug() << "stop" << " " << CHECKED;
            return;
        }
        buttonPosX += buttonStep;
    }else
    {
        if(buttonPosX <= startPos)
        {
            animationTimer.stop();
            CHECKED = !CHECKED;
            emit stateChanged(CHECKED);
            changeColor(!CHECKED);
            update();
            //qDebug() << "stop" << " " << CHECKED;
            return;
        }
        buttonPosX -= buttonStep;
    }
    update();
}

//设置开关状态
void
SwitchControl::setState(bool states)
{
  if(states == CHECKED)
  {
    return;
  }else
  {
    emit sig_buttonMove(CHECKED);
  }
    animationTimer.start(1);
}

void
SwitchControl::resizeEvent(QResizeEvent *event)
{
    baseSize = static_cast<qint16>(static_cast<qreal>(event->size().width()) /  baseWidthScale);
    translate();
    update();
}


void
SwitchControl::translate()
{
    //实际距离
    baseButtonDirection =  static_cast<int>(baseSize * baseButtonDirectionScale);
    baseWidth =  static_cast<int>(baseSize * baseWidthScale);
    baseHeight = static_cast<int>(baseSize * baseHeightScale);
    baseSlotWidth = static_cast<int>(baseSize * baseSlotWidthScale);
    baseSlotHeight = static_cast<int>(baseSize * baseSlotHeightScale);
    baseSlotRadius = static_cast<int>(baseSize * baseSlotRadiusScale);
}

void
SwitchControl::changeColor(bool checked)
{
    if(isEnabled())
    {
        if(!checked)
        {
            buttonColor = TrueButtonColor;
            slotColor = TrueSlotColor;
        }else
        {
            buttonColor = FalseButtonColor;
            slotColor = FalseSlotColor;
        }
    }else
    {
      buttonColor = DisableButtonColor;
      slotColor = DisableSlotColor;
    }
}

void
SwitchControl::resetDisableColor(QColor color)
{
  DisableButtonColor = color;
  DisableSlotColor = color;
  DisableSlotColor.setAlpha(150);
  update();
}
void
SwitchControl::resetTrueColor(QColor color)
{
  TrueButtonColor = color;
  TrueSlotColor = color;
  TrueSlotColor.setAlpha(150);
  update();
}
void
SwitchControl::resetFalseColor(QColor color)
{
  FalseButtonColor = color;
  FalseSlotColor = color;
  FalseSlotColor.setAlpha(150);
  update();
}
