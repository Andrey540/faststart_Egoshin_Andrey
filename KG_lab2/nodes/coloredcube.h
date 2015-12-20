#pragma once

#include "../gl/scenenode.h"
#include "iloadablenode.h"
#include <QVector3D>

class ColoredCube : public SceneNode, public ILoadableNode
{
public:
    ColoredCube(SceneNode *parent);

    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
    void load(const QJsonObjectWrapper &jsonObjWrapper) override;

private:
    QVector3D m_position;
    float m_scale = 1.0f;
    float m_angle = 0.0f;
    float m_speed = 0.0f;
};
