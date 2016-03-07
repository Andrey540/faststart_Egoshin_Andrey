#pragma once

#include "../gl/scenenode.h"
#include "iloadablenode.h"
#include <QVector3D>

class BaseSceneElement : public SceneNode, public ILoadableNode
{
public:
    BaseSceneElement(SceneNode *parent);

    void advance(int64_t msec) override;
    void render(QPainter &painter) override;
    void load(const QJsonObjectWrapper &jsonObjWrapper) = 0;

private:

    void drawOpenGLElement(bool showWired);
    void prepareVertices(bool showWired);

protected:

    virtual void drawFaces() = 0;
    virtual void generateVertices() = 0;

    QVector3D m_position;
    float m_scale = 1.0f;
    float m_angle = 0.0f;
    float m_speed = 0.0f;
    std::vector<SimpleVertex> m_vertices;
};

