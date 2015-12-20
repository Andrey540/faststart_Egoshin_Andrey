#ifndef QJSONOBJECTWRAPPER
#define QJSONOBJECTWRAPPER

#endif // QJSONOBJECTWRAPPER

#pragma once

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector3D>
#include <QString>
#include <memory>
#include <cstdio>
#include <cassert>

class QJsonObject;

class QJsonObjectWrapper
{
public:
    QJsonObjectWrapper(QJsonObject const& jsonObject);
    ~QJsonObjectWrapper();

    QVector3D getVector3D(const QLatin1String &key) const;
    QString getString(const QLatin1String &key) const;
    double getDouble(const QLatin1String &key) const;
private:

   QJsonObject m_jsonObject;
};

