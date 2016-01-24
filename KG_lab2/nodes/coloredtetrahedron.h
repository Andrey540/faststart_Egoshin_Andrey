#pragma once

#include "basesceneelement.h"

class ColoredTetrahedron : public BaseSceneElement
{
public:
    ColoredTetrahedron(SceneNode *parent);
    void load(const QJsonObjectWrapper &jsonObjWrapper) override;

protected:
    void drawFaces() override;
    void generateVertices() override;
};
