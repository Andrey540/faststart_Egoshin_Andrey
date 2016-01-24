#ifndef ROTATECAMERACONTROLLER
#define ROTATECAMERACONTROLLER

#endif // ROTATECAMERACONTROLLER

#include "iinputcontroller.h"
#include <QEvent>
#include <QResizeEvent>

class RotateCameraController : public IInputController
{
public:
    RotateCameraController();

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
    bool m_leftMouseButtomPressed = false;
    float m_horizontalCursorPosition = 0;
    float m_verticalCursorPosition = 0;
    float m_rotationZAngle = 0;
    float m_rotationYAngle = 0;
    float m_distance = 1.0f;
};

