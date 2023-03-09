#pragma once

#include <QtWidgets/QLineEdit>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT DragEdit : public QLineEdit
{
    Q_OBJECT
    
    Q_PROPERTY(float min_limit READ GetMinLimit WRITE SetMinLimit MEMBER min_limit_)
    Q_PROPERTY(float max_limit READ GetMaxLimit WRITE SetMaxLimit MEMBER max_limit_)
    Q_PROPERTY(float val       READ GetValue    WRITE SetValue    MEMBER value_)


public:
    explicit DragEdit(QWidget *parent = nullptr);

    inline float GetMinLimit() const          { return min_limit_; }
    inline void  SetMinLimit(float min_limit) { min_limit_ = min_limit; }

    inline float GetMaxLimit() const          { return max_limit_; }
    inline void  SetMaxLimit(float max_limit) { max_limit_ = max_limit; }

    inline float GetValue()    const          { return value_; }
    inline void  SetValue(float val)          { value_ = val; }

    inline float GetStep()     const          { return step_; }
    inline void  SetStep(float step)          { step_= step; }

protected:
    //void enterEvent       (QEnterEvent* event) override;
    //void leaveEvent       (QEvent*      event) override;
    void mouseMoveEvent   (QMouseEvent* event) override;
    void mousePressEvent  (QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    float min_limit_ = 0.0f;
    float max_limit_ = 99.9f;
    float step_      = 0.5f;
    float value_     = 50.0f;

    QPoint last_pos_  = QPoint(0, 0);
    bool   is_draged_ = false;
};
