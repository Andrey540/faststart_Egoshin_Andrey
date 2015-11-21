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
    void acceptEvent(QEvent *event) override;
    void updateCamera() override;

private:

    QVector3D m_eye;
    QVector3D m_at;
    QVector3D m_up;
    std::shared_ptr<BaseScene> m_scene;
    float m_positionX = 1.0f;
    float m_positionY = 1.0f;
    float m_positionZ = 1.0f;
};

