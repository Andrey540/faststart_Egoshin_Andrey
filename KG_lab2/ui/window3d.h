#pragma once

#include <QWindow>
#include <QOpenGLPaintDevice>
#include <QTime>
#include <memory>
#include "../gl/basescene.h"
#include "rotatecameracontroller.h"
#include "movecameracontroller.h"

class Window3D : public QWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(Window3D)

public:
    explicit Window3D(QWindow *parent = 0);
    void setFixedSize(QSize size);
    void pushScene(std::shared_ptr<BaseScene> scene);
    void popScene();

    bool event(QEvent *) override;

protected:
    void exposeEvent(QExposeEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void deferRender();
    void render();
    void stopRendering();
    void initRendering();
    void updateScene(BaseScene &scene);

private:
    QTime m_updateTime;
    bool m_canRender = false;
    bool m_updatePending = false;
    bool m_leftMouseButtomPressed = false;
    float m_horizontalCursorPosition = 0;
    float m_verticalCursorPosition = 0;
    float m_rotationZAngle = 0;
    float m_rotationYAngle = 0;
    float m_distance = 1.0f;
    std::shared_ptr<RotateCameraController> m_rotateCameraController;
    std::shared_ptr<MoveCameraController> m_moveCameraController;
    std::shared_ptr<IInputController> m_cameraController;
    std::vector<std::shared_ptr<BaseScene>> m_sceneStack;
    QOpenGLContext *m_pContext = nullptr;

    void changeCameraController();
};
