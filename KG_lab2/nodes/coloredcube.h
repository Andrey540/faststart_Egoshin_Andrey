#pragma once

#include "basesceneelement.h"

class ColoredCube : public BaseSceneElement
{
public:
    ColoredCube(SceneNode *parent);
    void load(const QJsonObjectWrapper &jsonObjWrapper) override;

protected:
    void drawFaces() override;
    void generateVertices() override;
};
