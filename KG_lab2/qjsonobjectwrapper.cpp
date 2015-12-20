#include "qjsonobjectwrapper.h"

QJsonObjectWrapper::QJsonObjectWrapper(QJsonObject const& jsonObject)
    : m_jsonObject(jsonObject)
{
}

QJsonObjectWrapper::~QJsonObjectWrapper()
{
}

QVector3D QJsonObjectWrapper::getVector3D(const QLatin1String &key) const
{
    QJsonArray array = m_jsonObject[key].toArray();
    if (array.size() != 3)
    {
        assert(!"incorrect array length");
    }

    float vecArray[3];
    int counter = 0;
    for (QJsonValue const& value : array)
    {
        vecArray[counter] = value.toDouble();
        ++counter;
    }
    return QVector3D(vecArray[0], vecArray[1], vecArray[2]);
}

QString QJsonObjectWrapper::getString(const QLatin1String &key) const
{
    return m_jsonObject[key].toString();
}

double QJsonObjectWrapper::getDouble(const QLatin1String &key) const
{
    return m_jsonObject[key].toDouble();
}
