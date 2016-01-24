#pragma once

#include "../gl/basescene.h"
#include "../gl/scenecamera.h"
#include <vector>
#include <QEvent>
#include <QResizeEvent>
#include <memory>

class IInputController
{
public:
    virtual ~IInputController() = default;

    virtual void setScene(std::shared_ptr<BaseScene> scene) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
    virtual void wheelEvent(QWheelEvent* event) = 0;
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    virtual void updateCamera() = 0;    
};
