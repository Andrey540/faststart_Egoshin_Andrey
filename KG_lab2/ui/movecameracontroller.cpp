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

void MoveCameraController::keyPressEvent(QKeyEvent* event)
{
    QVector2D front((m_at - m_eye).normalized());
    QVector2D tangent(front.y(), -front.x());
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
    {
        m_at  += -tangent;
        m_eye += -tangent;
    }
    if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
    {
        m_at  += tangent;
        m_eye += tangent;
    }
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
    {
        m_at  += front;
        m_eye += front;
    }
    if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
    {
        m_at  += -front;
        m_eye += -front;
    }
}

void MoveCameraController::updateCamera()
{
    if (m_scene)
    {
        m_scene->camera().lookAt(m_eye, m_at, m_up);
        m_scene->camera().loadMatrix();
    }
}

void MoveCameraController::wheelEvent(QWheelEvent* event)
{
    (void)event;
}

void MoveCameraController::mouseMoveEvent(QMouseEvent* event)
{
    (void)event;
}

void MoveCameraController::mousePressEvent(QMouseEvent* event)
{
    (void)event;
}

void MoveCameraController::mouseReleaseEvent(QMouseEvent* event)
{
    (void)event;
}
