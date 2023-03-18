#include "AcrInstrument/acrinstrument.h"

#include <QtWidgets/QToolTip>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QFont>
#include <QtGui/QMouseEvent>

AcrInstrument::AcrInstrument(QWidget *parent) : QWidget(parent)
{
  currentValue = 0;
  maxValue = 360;
  setMouseTracking(true);
  connect(&animationTimer,&QTimer::timeout,this,&AcrInstrument::slot_changeAnimation);
  bottomString = QString("default");
}

void AcrInstrument::setMaxValue(int value)
{
  this->maxValue = value;
}

void AcrInstrument::setValue(int value)
{
  currentAngle = value2angle(currentValue);
  targetAngle = value2angle(value);
  targetValue = value;
  animationTimer.start(2);
}

void AcrInstrument::setNormalColor(QColor color)
{
  this->normalColor = color;
}

void AcrInstrument::setWarningColor(QColor color)
{
  this->warningColor = color;
}

void AcrInstrument::setDangerColor(QColor color)
{
  this->dangerColor = color;
}

void AcrInstrument::setBaseSize(int size)
{
  this->baseSize = size;
  outsideArcRadius= static_cast<int>(baseSize * outsideArcRadiusScale);
  insideArcRadius= static_cast<int>(baseSize * insideArcRadiusScale);
  fontSize = static_cast<int>(baseSize * valueFontSizeScale);
  bottomFontSize = static_cast<int>(baseSize * bottomFontSizeScale);
  update();
}

void AcrInstrument::setBottomString(QString str)
{
  this->bottomString = str;
}

int AcrInstrument::getCurrentValue()
{
  return this->currentValue;
}

int AcrInstrument::getMaxValue()
{
  return this->maxValue;
}

void AcrInstrument::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)

  QPainter painter(this);
  QBrush brush;
  QColor color;

  angle = currentAngle;

  if(currentAngle < 360 * warningLevel)
  {
    color = normalColor;
  }else
  {
    if(currentAngle < 360 * dangerLevel)
      color = warningColor;
    else
      color = dangerColor;
  }


  QPainterPath path;      //主要的旋转部分
  QPainterPath subPath;   //去掉中间的部分
  QPainterPath fontPath;  //value字体的显示
  QPainterPath linePath;  //分割线
  QPainterPath unitPath;  //单位显示


  painter.setWindow(-width() / 2, -height() / 2, width(), height());
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setBrush(color);

  QRect rect(-outsideArcRadius, -outsideArcRadius, outsideArcRadius << 1, outsideArcRadius << 1);
  QRect rect2(-insideArcRadius,-insideArcRadius, insideArcRadius << 1, insideArcRadius << 1);
  //path.moveTo(50,50);
  path.arcTo(rect,0,-angle);
  subPath.arcTo(rect2,0,360);
  painter.setPen(Qt::NoPen);

  path -= subPath;
  painter.drawPath(path);

  //字体设置
  painter.setPen(QColor(color));
  QRect fontRect = QRect(-insideArcRadius / 1.414,
                         -fontSize * 1.75,
                         insideArcRadius / 1.414 * 2,
                         insideArcRadius / 1.414 * 2);
  QFont valueFont;
  valueFont.setFamily("微软雅黑");
  valueFont.setPixelSize(fontSize);
  valueFont.setPointSize(fontSize);
  painter.setFont(valueFont);
  QString str_number;
  if (dataType == INT)
  {
    str_number= QString::number((int)currentRealValue_);
  }
  else
  {
    str_number = QString::number(currentRealValue_,'f',2);

  }
  painter.drawText(fontRect,Qt::AlignHCenter,str_number);
  //显示单位
  painter.setPen(Qt::white);
  QRect unitFontRect = QRect(-insideArcRadius / 1.414,
                             fontSize*0.5,
                             insideArcRadius / 1.414 * 2,
                             insideArcRadius / 1.414 * 2);
  QFont unitFont;
  unitFont.setFamily("微软雅黑");
  unitFont.setPixelSize(bottomFontSize);
  unitFont.setPointSize(bottomFontSize);
  painter.setFont(unitFont);
  painter.drawText(unitFontRect,Qt::AlignHCenter,bottomString);


  // 画一条分界线
  painter.drawLine(-insideArcRadius / 1.414,fontSize*0.25,insideArcRadius/ 1.414,fontSize*0.25);

}

//void AcrInstrument::mouseMoveEvent(QMouseEvent *event)
//{
//  QString Pos = QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());
//  QToolTip::showText(event->globalPos(),Pos,this);
//}

void AcrInstrument::resizeEvent(QResizeEvent *event)
{
  baseSize = event->size().width();
}

int AcrInstrument::sign(int x)
{
    return x>=0?1:-1;
}

int AcrInstrument::mapReal2Int(const qreal _realValue)
{
    qreal result = (_realValue - minRealValue_) / (maxRealValue_ - minRealValue_) * maxValue;
    return static_cast<int>(result);
}

int AcrInstrument::value2angle(int value)
{
  //qDebug() << value * 360 / getMaxValue();
  return value * 360 / getMaxValue();
}

void AcrInstrument::slot_changeAnimation()
{
  deltaAngle = targetAngle - currentAngle;

  int angleStep = sign(deltaAngle) * 10;
  if(abs(deltaAngle) < 10)
    angleStep = sign(deltaAngle) * 1;

  if(deltaAngle == 0) //说明此时已经旋转到target的位置
  {
    animationTimer.stop(); //计时器停止
    currentValue = targetValue; //当前值与目标值相同
  }else
  {
    currentValue = currentAngle * getMaxValue() / 360;
    currentAngle += angleStep;
  }
  update();
}
