#include "coloredtetrahedron.h"

static const QLatin1String KEY_TETRAHEDRON_SCALE("scale");
static const QLatin1String KEY_TETRAHEDRON_POSITION("position");

ColoredTetrahedron::ColoredTetrahedron(SceneNode *parent)
    : BaseSceneElement(parent)
{}

void ColoredTetrahedron::generateVertices()
{
    m_vertices.clear();
    m_vertices.push_back({{-1, -1, -1}, {0, 255, 0, 255}});
    m_vertices.push_back({{+1, +1, -1}, {0, 255, 0, 255}});
    m_vertices.push_back({{+1, -1, -1}, {0, 255, 0, 255}});

    m_vertices.push_back({{-1, -1, -1}, {0, 255, 0, 255}});
    m_vertices.push_back({{-1, +1, -1}, {0, 255, 0, 255}});
    m_vertices.push_back({{+1, +1, -1}, {0, 255, 0, 255}});

    m_vertices.push_back({{-1, -1, -1}, {255, 0, 0, 255}});
    m_vertices.push_back({{+1, -1, -1}, {255, 0, 0, 255}});
    m_vertices.push_back({{0, 0, +0.5}, {255, 0, 0, 255}});

    m_vertices.push_back({{-1, +1, -1}, {0, 100, 255, 255}});
    m_vertices.push_back({{0, 0, +0.5}, {0, 100, 255, 255}});
    m_vertices.push_back({{+1, +1, -1}, {0, 100, 255, 255}});

    m_vertices.push_back({{-1, -1, -1}, {0, 255, 255, 255}});
    m_vertices.push_back({{0, 0, +0.5}, {0, 255, 255, 255}});
    m_vertices.push_back({{-1, +1, -1}, {0, 255, 255, 255}});

    m_vertices.push_back({{+1, -1, -1}, {255, 255, 0, 255}});
    m_vertices.push_back({{+1, +1, -1}, {255, 255, 0, 255}});
    m_vertices.push_back({{0, 0, +0.5}, {255, 255, 0, 255}});
}

void ColoredTetrahedron::drawFaces()
{
    // Массив граней, а точнее, индексов составляющих их вершин.
    // Индексы вершин граней перечисляются в порядке их обхода
    // против часовой стрелки (если смотреть на грань снаружи)
    const unsigned char faces[6][3] =
    {
        {12, 13, 14},
        {9, 10, 11},
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {15, 16, 17},
    };

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, faces);
}

void ColoredTetrahedron::load(const QJsonObjectWrapper &jsonObjWrapper)
{
    m_scale = jsonObjWrapper.getDouble(KEY_TETRAHEDRON_SCALE);
    m_position = jsonObjWrapper.getVector3D(KEY_TETRAHEDRON_POSITION);
}
