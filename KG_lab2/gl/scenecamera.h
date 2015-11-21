#pragma once

#include <QObject>
#include <QVector3D>
#include <QSize>
#include <stdint.h>

typedef std::pair<float, QVector3D> Rotation;

/// Static camera, can be manually controlled.
class SceneCamera : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SceneCamera)
    Q_PROPERTY(QSize viewport READ viewport WRITE setViewport)
    Q_PROPERTY(QVector3D eye READ eye)
public:
    explicit SceneCamera(QSize viewport, QObject *parent = 0);

    void loadMatrix();
    void rotate(float angle, const QVector3D &vec);
    void translate(float positionX, float positionY, float positionZ);
    void lookAt(QVector3D const &eye, QVector3D const& at, QVector3D const& up);
    /// @param msec - milliseconds since last advance or creation.
    void advance(int64_t msec);

    QSize viewport() const;
    void setViewport(QSize viewport);
    QVector3D eye() const;
    QVector3D at() const;
    QVector3D up() const;
    void setSpeed(QVector3D speed);
    QVector3D speed() const;    

protected:

private:
    void doRotates(QMatrix4x4 &matrix);
    void doTranslate(QMatrix4x4 &matrix);

private:
    QSize m_viewport;
    QVector3D m_eye;   /**< Eye position */
    QVector3D m_front; /**< Front direction */
    QVector3D m_up;    /**< Up direction */
    QVector3D m_speed; /**< Speed, meters per second, front/left/up */
    std::vector<Rotation> m_rotations;
    float m_positionX = 0.5f;
    float m_positionY = 0.5f;
    float m_positionZ = 0.5f;
};
