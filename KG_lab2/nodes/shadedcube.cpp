#include "shadedcube.h"

static const QLatin1String KEY_CUBE_SCALE("scale");
static const QLatin1String KEY_CUBE_POSITION("position");

ShadedCube::ShadedCube(SceneNode *parent)
    : BaseSceneElement(parent)
{}

void ShadedCube::generateVertices()
{
    m_vertices.clear();
    m_vertices.push_back({{-1, -1, -1}, {0, 155, 0, 255}});
    m_vertices.push_back({{+1, -1, -1}, {0, 155, 0, 255}});
    m_vertices.push_back({{+1, +1, -1}, {0, 155, 0, 255}});
    m_vertices.push_back({{-1, +1, -1}, {0, 155, 0, 255}});
    m_vertices.push_back({{-1, -1, +1}, {0, 155, 0, 255}});
    m_vertices.push_back({{+1, -1, +1}, {0, 155, 0, 255}});
    m_vertices.push_back({{+1, +1, +1}, {0, 155, 0, 255}});
    m_vertices.push_back({{-1, +1, +1}, {0, 155, 0, 255}});

    m_vertices.push_back({{-1, -1, +1}, {0, 255, 0, 255}});
    m_vertices.push_back({{+1, -1, +1}, {0, 255, 0, 255}});
    m_vertices.push_back({{+1, +1, +1}, {0, 255, 0, 255}});
    m_vertices.push_back({{-1, +1, +1}, {0, 255, 0, 255}});
}

void ShadedCube::drawFaces()
{
    // Массив граней, а точнее, индексов составляющих их вершин.
    // Индексы вершин граней перечисляются в порядке их обхода
    // против часовой стрелки (если смотреть на грань снаружи)
    const unsigned char faces[6][4] =
    {
        {4, 7, 3, 0},	// грань x<0
        {5, 1, 2, 6},	// грань x>0
        {4, 0, 1, 5},	// грань y<0
        {7, 6, 2, 3},	// грань y>0
        {0, 3, 2, 1},	// грань z<0
        {8, 9, 10, 11},	// грань z>0
    };

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);
}

void ShadedCube::load(const QJsonObjectWrapper &jsonObjWrapper)
{
    m_scale = jsonObjWrapper.getDouble(KEY_CUBE_SCALE);
    m_position = jsonObjWrapper.getVector3D(KEY_CUBE_POSITION);
}
