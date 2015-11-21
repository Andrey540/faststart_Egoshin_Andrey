#include "rotatecameracontroller.h"
#include <memory>

RotateCameraController::RotateCameraController()
{}

void RotateCameraController::setScene(std::shared_ptr<BaseScene> scene)
{
    m_scene = scene;
    m_eye = scene->camera().eye();
    m_at  = scene->camera().at();
    m_up  = scene->camera().up();
}

void RotateCameraController::acceptEvent(QEvent *event)
{
    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        processWheelEvent(wheelEvent);
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        processMouseMoveEvent(mouseEvent);
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        processMousePressEvent(mouseEvent);
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        processMouseReleaseEvent(mouseEvent);
    }
}

void RotateCameraController::updateCamera()
{
    if (m_scene)
    {
        m_scene->camera().lookAt(m_eye * m_distance, m_at, m_up);
        m_scene->camera().rotate(m_rotationYAngle, QVector3D(0, 1, 0));
        m_scene->camera().rotate(m_rotationZAngle, QVector3D(0, 0, 1));
        m_scene->camera().loadMatrix();
    }
}

void RotateCameraController::processWheelEvent(QWheelEvent* event)
{
    int numDegrees = event->delta() / 8;
    float numSteps = numDegrees / 30.0f;

    if (event->orientation() == Qt::Vertical)
    {
        m_distance += numSteps;
        m_distance = qMax(1.0f, m_distance);
        m_distance = qMin(5.0f, m_distance);
    }
}

void RotateCameraController::processMouseMoveEvent(QMouseEvent* event)
{
    if (m_leftMouseButtomPressed)
    {
        m_rotationZAngle += event->x() - m_horizontalCursorPosition;
        m_rotationYAngle += event->y() - m_verticalCursorPosition;
        m_horizontalCursorPosition = event->x();
        m_verticalCursorPosition   = event->y();

        m_rotationYAngle = qMax(0.0f, m_rotationYAngle);
        m_rotationYAngle = qMin(90.0f, m_rotationYAngle);
    }
}

void RotateCameraController::processMousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtomPressed = true;
        m_horizontalCursorPosition = event->x();
        m_verticalCursorPosition   = event->y();
    }
}

void RotateCameraController::processMouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtomPressed = false;
    }
}
