#include "coloredtetrahedron.h"

static const QLatin1String KEY_TETRAHEDRON_SCALE("scale");
static const QLatin1String KEY_TETRAHEDRON_POSITION("position");

static void drawOpenGLTetrahedron(bool showWired, float scale, QVector3D position)
{
    /*

       Y
       |
       |
       |
       +---X
      /
     /
    Z

    */
    // Массив координат вершин
    SimpleVertex vertices[18] =
    {
        {{-1, -1, -1}, {0, 255, 0, 255}},	// 0
        {{+1, +1, -1}, {0, 255, 0, 255}},	// 2
        {{+1, -1, -1}, {0, 255, 0, 255}},	// 1        

        {{-1, -1, -1}, {0, 255, 0, 255}},	// 0
        {{-1, +1, -1}, {0, 255, 0, 255}},	// 3
        {{+1, +1, -1}, {0, 255, 0, 255}},	// 2

        {{-1, -1, -1}, {255, 0, 0, 255}},	// 0
        {{+1, -1, -1}, {255, 0, 0, 255}},	// 1
        {{0, 0, +0.5}, {255, 0, 0, 255}},	// 4

        {{-1, +1, -1}, {0, 100, 255, 255}},	// 3
        {{0, 0, +0.5}, {0, 100, 255, 255}},	// 4
        {{+1, +1, -1}, {0, 100, 255, 255}},	// 2

        {{-1, -1, -1}, {0, 255, 255, 255}},	// 0
        {{0, 0, +0.5}, {0, 255, 255, 255}},	// 4
        {{-1, +1, -1}, {0, 255, 255, 255}},	// 3

        {{+1, -1, -1}, {255, 255, 0, 255}},	// 1
        {{+1, +1, -1}, {255, 255, 0, 255}},	// 2
        {{0, 0, +0.5}, {255, 255, 0, 255}},	// 4
    };

    for (SimpleVertex &vert : vertices) {
        vert.pos.x += position.x();
        vert.pos.y += position.y();
        vert.pos.z += position.z();
        vert.pos.x *= scale;
        vert.pos.y *= scale;
        vert.pos.z *= scale;
    }

    if (showWired) {
        for (SimpleVertex &vert : vertices) {
            vert.pos.x *= 1.01;
            vert.pos.y *= 1.01;
            vert.pos.z *= 1.01;
            vert.color.r = 0;
            vert.color.g = 0;
            vert.color.b = 0;
        }
    }

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

    // Передаем информацию о массиве вершин
    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

    // и массиве цветов
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    // Разрешаем использование массива координат вершин и цветов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, faces);

    // Выключаем использовнием массива цветов
    glDisableClientState(GL_COLOR_ARRAY);
    // Выключаем использование массива координат вершин
    glDisableClientState(GL_VERTEX_ARRAY);
}

ColoredTetrahedron::ColoredTetrahedron(SceneNode *parent)
    : SceneNode(parent)
{
}

void ColoredTetrahedron::advance(int64_t msec)
{
    (void)msec;
}

void ColoredTetrahedron::render(QPainter &painter)
{
    (void)painter;

    drawOpenGLTetrahedron(false, m_scale, m_position);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawOpenGLTetrahedron(true, m_scale, m_position);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ColoredTetrahedron::load(const QJsonObject &jsonObj)
{
    m_scale = jsonObj[KEY_TETRAHEDRON_SCALE].toDouble();
    m_position = ParseUtils::parseVector3D(jsonObj[KEY_TETRAHEDRON_POSITION].toArray());
}
