#ifndef __VECTOR3_EDITOR_H
#define __VECTOR3_EDITOR_H

#include <QtWidgets/QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QtGui/QVector3D>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Vector3Edit;
}
QT_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT Vector3Edit : public QWidget
{
    Q_OBJECT
    
    Q_PROPERTY(QVector3D vector MEMBER vector_ NOTIFY VectorChanged READ GetValue WRITE SetValue)

public:
    explicit Vector3Edit(QWidget* parent = nullptr, QVector3D vector = QVector3D());
    ~Vector3Edit();

    inline QVector3D GetValue()  const { return vector_; }
    void             SetValue(const QVector3D& value);
    
    inline float     GetX()      const { return vector_[0]; }
    void             SetX(float val);
        
    inline float     GetY()      const { return vector_[1]; }
    void             SetY(float val);
    
    inline float     GetZ()      const { return vector_[2]; }
    void             SetZ(float val);

    void             SetXRange(float lower, float upper);
    void             SetYRange(float lower, float upper);
    void             SetZRange(float lower, float upper);
    void             SetRange (float lower, float upper);

    void             SetStep  (float step);

signals:
    void VectorChanged(const QVector3D& Vector);

private:
    QVector3D        vector_;
    Ui::Vector3Edit* ui_ptr_;
};


#endif // !__VECTOR3_EDITOR_H