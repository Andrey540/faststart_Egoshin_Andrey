#ifndef SCENEDESERIALIZER
#define SCENEDESERIALIZER

#endif // SCENEDESERIALIZER

#pragma once

#include "gl/basescene.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <memory>
#include <cstdio>
#include <cassert>

class QJsonObject;

class SceneDeserializer
{
public:
    SceneDeserializer(QString const& filepath);
    ~SceneDeserializer();

    bool load(std::shared_ptr<BaseScene> scene);

private:
    void deserialize(const QJsonObject &source, std::shared_ptr<BaseScene> scene);
    QVector3D parseVector3D(const QJsonArray& array) const;

    const QString m_filepath;
};

