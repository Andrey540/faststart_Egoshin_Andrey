#ifndef MOVECAMERACONTROLLER
#define MOVECAMERACONTROLLER

#endif // MOVECAMERACONTROLLER

#include "iinputcontroller.h"
#include <QEvent>
#include <QResizeEvent>

class MoveCameraController : public IInputController
{
public:
    MoveCameraController();

    void setScene(std::shared_ptr<BaseScene> scene) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void updateCamera() override;

private:
    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;
    std::shared_ptr<BaseScene> m_scene;
};

