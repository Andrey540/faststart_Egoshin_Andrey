#pragma once

#include "../gl/scenenode.h"
#include "iloadablenode.h"
#include "../parseutils.h"
#include <QVector3D>

class ShadedCube : public SceneNode, public ILoadableNode
{
public:
    ShadedCube(SceneNode *parent);

    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
    void load(const QJsonObject &jsonObj) override;

private:
    QVector3D m_position;
    float m_scale = 1.0f;
};
