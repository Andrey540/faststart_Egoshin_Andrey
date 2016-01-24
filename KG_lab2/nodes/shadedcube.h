#pragma once

#include "basesceneelement.h"

class ShadedCube : public BaseSceneElement
{
public:
    ShadedCube(SceneNode *parent);
    void load(const QJsonObjectWrapper &jsonObjWrapper) override;

protected:
    void drawFaces() override;
    void generateVertices() override;
};
