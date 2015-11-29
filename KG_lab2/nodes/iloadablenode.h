#pragma once

#include <qopengl.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QPainter>


// Структура - трехмерный вектор
struct Vec3
{
    GLfloat x, y, z;
};

// Структура - четырехкомпонентный цвет
struct Color4
{
    GLubyte r, g, b, a;
};

// Структура - вершина
struct SimpleVertex
{
    Vec3 pos;
    Color4 color;
};

class ILoadableNode
{
public:
    virtual ~ILoadableNode() = default;

    virtual void load(const QJsonObject &jsonObj) = 0;
};
