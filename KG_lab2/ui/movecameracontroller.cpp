#include "movecameracontroller.h"
#include <memory>

MoveCameraController::MoveCameraController()
{}

void MoveCameraController::setScene(std::shared_ptr<BaseScene> scene)
{
    m_scene = scene;
    m_eye = scene->camera().eye();
    m_at  = scene->camera().at();
    m_up  = scene->camera().up();
}

void MoveCameraController::acceptEvent(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
         QKeyEvent *key = static_cast<QKeyEvent*>(event);
         if (key->key() == Qt::Key_A || key->key() == Qt::Key_Left)
         {
             m_positionY -= 0.3f;
         }
         if (key->key() == Qt::Key_D || key->key() == Qt::Key_Right)
         {
             m_positionY += 0.3f;
         }
         if (key->key() == Qt::Key_W || key->key() == Qt::Key_Up)
         {
             m_positionX += 0.3f;
         }
         if (key->key() == Qt::Key_S || key->key() == Qt::Key_Down)
         {
             m_positionX -= 0.3f;
         }
    }
}

void MoveCameraController::updateCamera()
{
    if (m_scene)
    {
        m_scene->camera().lookAt(m_eye, m_at, m_up);
        m_scene->camera().translate(m_positionX, m_positionY, m_positionZ);
        m_scene->camera().loadMatrix();
    }
}
