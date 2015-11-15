#include "window3d.h"
#include <QResizeEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QDebug>

Window3D::Window3D(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->installEventFilter(this);
}

void Window3D::setFixedSize(QSize size)
{
    setMinimumSize(size);
    setMaximumSize(size);
}

void Window3D::pushScene(std::shared_ptr<BaseScene> scene)
{
    m_sceneStack.push_back(scene);
    scene->onPush();
}

void Window3D::popScene()
{
    if (!m_sceneStack.empty())
    {
        m_sceneStack.back()->onPop();
        m_sceneStack.pop_back();
    }
}

bool Window3D::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_updatePending = false;
        render();
        return true;
    case QEvent::Close:
        if (m_canRender)
        {
            stopRendering();
        }
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void Window3D::exposeEvent(QExposeEvent *event)
{
    QWindow::exposeEvent(event);
    if (isExposed())
        render();
}

void Window3D::resizeEvent(QResizeEvent *event)
{
    QWindow::resizeEvent(event);
    if (!m_canRender)
    {
        initRendering();
    }
}

void Window3D::showEvent(QShowEvent *event)
{
    QWindow::showEvent(event);
}

void Window3D::deferRender()
{
    if (!m_updatePending) {
        m_updatePending = true;
        QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void Window3D::render()
{
    if (!m_canRender)
    {
        return;
    }

    m_pContext->makeCurrent(this);
    if (!m_sceneStack.empty())
    {
        updateScene(*m_sceneStack.back());
    }
    else
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    m_pContext->swapBuffers(this);
    deferRender();
}

void Window3D::stopRendering()
{
    while (!m_sceneStack.empty())
    {
        popScene();
    }
    m_canRender = false;
}

void Window3D::initRendering()
{
    if (!m_pContext) {
        m_pContext = new QOpenGLContext(this);
        m_pContext->setFormat(requestedFormat());
        m_pContext->create();
    }
    m_canRender = true;
    m_updateTime.start();
}

void Window3D::updateScene(BaseScene &scene)
{
    scene.setViewport(size());

    int msec = m_updateTime.elapsed();
    m_updateTime.restart();
    scene.visit([&](SceneNode & node) {
        node.advance(msec);
    });
    scene.camera().advance(msec);

    QOpenGLPaintDevice device(size());
    QPainter painter(&device);
    scene.camera().rotate(m_rotationAngle, QVector3D(6, 3, 2));
    scene.camera().loadMatrix();    
    scene.render(painter);
    scene.visit([&](SceneNode & node) {
        node.render(painter);
    });
}

void Window3D::mouseMoveEvent(QMouseEvent *event)
{
    if (m_leftMouseButtomPressed)
    {
        m_rotationAngle += event->x() - m_horizontalCursorPosition;
        m_horizontalCursorPosition = event->x();
    }
}

void Window3D::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtomPressed = true;
        m_horizontalCursorPosition = event->x();
    }
}

void Window3D::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtomPressed = false;
    }
}
