#include "shadedcube.h"

static const QLatin1String KEY_CUBE_SCALE("scale");
static const QLatin1String KEY_CUBE_POSITION("position");

static void drawOpenGLCube(bool showWired, float scale, QVector3D position)
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
       3----2
      /    /|
     /    / |
(11)7----6(10)
    |  0 |  1
    |    | /
    |    |/
 (8)4----5(9)
    */
    // Массив координат вершин
    SimpleVertex vertices[12] =
    {
        {{-1, -1, -1}, {0, 155, 0, 255}},	// 0
        {{+1, -1, -1}, {0, 155, 0, 255}},	// 1
        {{+1, +1, -1}, {0, 155, 0, 255}},	// 2
        {{-1, +1, -1}, {0, 155, 0, 255}},	// 3
        {{-1, -1, +1}, {0, 155, 0, 255}},	// 4
        {{+1, -1, +1}, {0, 155, 0, 255}},	// 5
        {{+1, +1, +1}, {0, 155, 0, 255}},	// 6
        {{-1, +1, +1}, {0, 155, 0, 255}},	// 7

        {{-1, -1, +1}, {0, 255, 0, 255}},	// 8
        {{+1, -1, +1}, {0, 255, 0, 255}},	// 9
        {{+1, +1, +1}, {0, 255, 0, 255}},	// 10
        {{-1, +1, +1}, {0, 255, 0, 255}},	// 11
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
    const unsigned char faces[6][4] =
    {
        {4, 7, 3, 0},	// грань x<0
        {5, 1, 2, 6},	// грань x>0
        {4, 0, 1, 5},	// грань y<0
        {7, 6, 2, 3},	// грань y>0
        {0, 3, 2, 1},	// грань z<0
        {8, 9, 10, 11},	// грань z>0
    };

    // Передаем информацию о массиве вершин
    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &vertices[0].pos);

    // и массиве цветов
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &vertices[0].color);

    // Разрешаем использование массива координат вершин и цветов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, faces);

    // Выключаем использовнием массива цветов
    glDisableClientState(GL_COLOR_ARRAY);
    // Выключаем использование массива координат вершин
    glDisableClientState(GL_VERTEX_ARRAY);
}

ShadedCube::ShadedCube(SceneNode *parent)
    : SceneNode(parent)
{
}

void ShadedCube::advance(int64_t msec)
{
    (void)msec;
}

void ShadedCube::render(QPainter &painter)
{
    (void)painter;

    drawOpenGLCube(false, m_scale, m_position);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawOpenGLCube(true, m_scale, m_position);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ShadedCube::load(const QJsonObjectWrapper &jsonObjWrapper)
{
    m_scale = jsonObjWrapper.getDouble(KEY_CUBE_SCALE);
    m_position = jsonObjWrapper.getVector3D(KEY_CUBE_POSITION);
}
