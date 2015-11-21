#pragma once

#include "../gl/basescene.h"
#include "../gl/scenecamera.h"
#include <vector>
#include <QEvent>
#include <memory>

class IInputController
{
public:
    virtual ~IInputController() = default;

    virtual void setScene(std::shared_ptr<BaseScene> scene) = 0;
    virtual void acceptEvent(QEvent *event) = 0;
    virtual void updateCamera() = 0;
};
