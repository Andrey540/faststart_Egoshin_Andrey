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

void RotateCameraController::wheelEvent(QWheelEvent* event)
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

void RotateCameraController::mouseMoveEvent(QMouseEvent* event)
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

void RotateCameraController::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtomPressed = true;
        m_horizontalCursorPosition = event->x();
        m_verticalCursorPosition   = event->y();
    }
}

void RotateCameraController::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtomPressed = false;
    }
}

void RotateCameraController::keyPressEvent(QKeyEvent* event)
{
    (void)event;
}
