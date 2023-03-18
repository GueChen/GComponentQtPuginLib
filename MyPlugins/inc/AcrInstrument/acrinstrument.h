/** 
 *  @author CC
 **/
#ifndef ACRINSTRUMENT_H
#define ACRINSTRUMENT_H

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>

class AcrInstrument : public QWidget
{
public:
  enum AcrDataType
  {
    INT = 0,  //DATA TYPE integer
    REAL = 1 //DATA TYPE float or double
  };

    Q_OBJECT
public:
    explicit AcrInstrument(QWidget *parent = nullptr);

    void setNormalColor(QColor color);
    void setWarningColor(QColor color);
    void setDangerColor(QColor color);
    void setBaseSize(int size);
    void setBottomString(QString str);


    void setMaxRealValue(const qreal _maxRealValue) {maxRealValue_ = _maxRealValue;}
    void setMinRealValue(const qreal _minRealValue) {minRealValue_ = _minRealValue;}
    void setRealValue(const qreal _realValue)
    {
        currentRealValue_ = _realValue;
        setValue(mapReal2Int(currentRealValue_));
    }

    void setDataType(AcrDataType _dt){dataType = _dt;}

private:
    void setMaxValue(int value);
    void setValue(int value);
    int getCurrentValue();
    int getMaxValue();

protected:
    void paintEvent(QPaintEvent *event) override;
    //void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:

    QColor normalColor = QColor(0,200,0);
    QColor warningColor = QColor(200,200,0);
    QColor dangerColor = QColor(200,0,0);

    //真实值
    qreal maxRealValue_ = 10.0;
    qreal minRealValue_ = 0.0;
    qreal currentRealValue_ = 0.0;

    //实际控制值
    int maxValue = 1800;
    int currentValue;

    int angle;

    QString bottomString;
    //图形各部分所占比例
    qreal outsideArcRadiusScale = 1.0;
    qreal insideArcRadiusScale = 0.7;
    qreal valueFontSizeScale = 0.3;
    qreal bottomFontSizeScale = 0.18;
    //基础像素大小
    int baseSize = 50;
    //转换后图形各部分所占绝对像素值
    int outsideArcRadius= static_cast<int>(baseSize * outsideArcRadiusScale);
    int insideArcRadius= static_cast<int>(baseSize * insideArcRadiusScale);
    int fontSize = static_cast<int>(baseSize * valueFontSizeScale);
    int bottomFontSize = static_cast<int>(baseSize * bottomFontSizeScale);

    //变色水平(阈值)
    const qreal warningLevel = 0.8;
    const qreal dangerLevel = 0.95;

    //动画相关
    QTimer animationTimer;

    int targetAngle;
    int currentAngle;
    int deltaAngle;
    int targetValue;
    AcrDataType dataType = INT;

    ///////////////////////////////////////////////////////////////////////
    int value2angle(int value);
    int sign(int x);
    int mapReal2Int(const qreal _realValue);


signals:
    void valueChanged(int value);
private slots:
    void slot_changeAnimation();

};

#endif // ACRINSTRUMENT_H
