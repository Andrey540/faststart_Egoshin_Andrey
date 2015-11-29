#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QPainter>
#include <QVector3D>
#include <cstdio>
#include <cassert>

class ParseUtils
{
public:
    static QVector3D parseVector3D(const QJsonArray &array)
    {
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
};
