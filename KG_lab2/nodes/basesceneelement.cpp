#include "basesceneelement.h"
#include <QMatrix4x4>

BaseSceneElement::BaseSceneElement(SceneNode *parent)
    : SceneNode(parent)
{
}

void BaseSceneElement::drawOpenGLElement(bool showWired)
{
    prepareVertices(showWired);

    // Передаем информацию о массиве вершин
    glVertexPointer(3, GL_FLOAT, sizeof(SimpleVertex), &m_vertices[0].pos);

    // и массиве цветов
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(SimpleVertex), &m_vertices[0].color);

    // Разрешаем использование массива координат вершин и цветов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    drawFaces();

    // Выключаем использовнием массива цветов
    glDisableClientState(GL_COLOR_ARRAY);
    // Выключаем использование массива координат вершин
    glDisableClientState(GL_VERTEX_ARRAY);
}

void BaseSceneElement::prepareVertices(bool showWired)
{
    generateVertices();

    QMatrix4x4 matrix;
    matrix.scale(m_scale);
    matrix.translate(m_position);
    matrix.rotate(m_angle, 0.0, 0.0, 1.0);

    for (SimpleVertex &vert : m_vertices) {
        QVector3D p(vert.pos.x, vert.pos.y, vert.pos.z);
        p = matrix * p;
        vert.pos.x = p.x();
        vert.pos.y = p.y();
        vert.pos.z = p.z();
    }

    if (showWired) {
        for (SimpleVertex &vert : m_vertices) {
            vert.pos.x *= 1.01;
            vert.pos.y *= 1.01;
            vert.pos.z *= 1.01;
            vert.color.r = 0;
            vert.color.g = 0;
            vert.color.b = 0;
        }
    }
}

void BaseSceneElement::advance(int64_t msec)
{
    (void)msec;
}

void BaseSceneElement::render(QPainter &painter)
{
    (void)painter;

    drawOpenGLElement(false);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawOpenGLElement(true);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_angle = (m_angle + m_speed);
}
