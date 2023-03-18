/**
 *  @author CC
 **/
#ifndef SwitchControl_H
#define SwitchControl_H

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>

class SwitchControl : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchControl(QWidget *parent = nullptr);

    //读取开关状态
    bool isChecked() const {return CHECKED;}

    //设置开关状态
    void setState(bool states);
    void resetDisableColor(QColor color);
    void resetTrueColor(QColor color);
    void resetFalseColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    QSize sizeHint() const override;


private:
    /************************
     * 逻辑相关
     * *********************/
    bool CHECKED;
    /************************
     * 图形相关
     * *********************/

    //图形比例
    qint16 baseSize = 40;
    qreal baseButtonDirectionScale = 0.9;
    qreal baseWidthScale = 2.2;
    qreal baseHeightScale = 1.2;
    qreal baseSlotWidthScale = 0.8;
    qreal baseSlotHeightScale = 0.45;
    qreal baseSlotRadiusScale = baseSlotHeightScale / 2;

    //实际距离
    int baseButtonDirection =  static_cast<int>(baseSize * baseButtonDirectionScale);
    int baseWidth =  static_cast<int>(baseSize * baseWidthScale);
    int baseHeight = static_cast<int>(baseSize * baseHeightScale);
    int baseSlotWidth = static_cast<int>(baseSize * baseSlotWidthScale);
    int baseSlotHeight = static_cast<int>(baseSize * baseSlotHeightScale);
    int baseSlotRadius = static_cast<int>(baseSize * baseSlotRadiusScale);

    //颜色
    QColor FalseSlotColor = QColor(200,200,200,150);
    QColor FalseButtonColor = QColor(200,200,200);

    QColor TrueSlotColor = QColor(0,190,190,150);
    QColor TrueButtonColor = QColor(0,190,190);

    QColor DisableSlotColor = QColor(120,120,120,150);
    QColor DisableButtonColor = QColor(120,120,120);

    QColor slotColor = FalseSlotColor;
    QColor buttonColor = FalseButtonColor;

    //动画相关
    const int startPos =  - (baseSlotWidth / 2);
    const int stopPos =   baseSlotWidth / 2;

    int buttonPosX;
    int buttonPosY;
    int buttonStep = 5;
    
    QTimer animationTimer;

    //功能函数
    void translate();
    void changeColor(bool checked);
signals:
    void sig_buttonMove(bool checked);
    void stateChanged(bool checked);
private slots:
    void slot_stateChangedAnimation();
};

#endif // SwitchControl_H
