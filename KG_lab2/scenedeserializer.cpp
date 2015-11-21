#include "scenedeserializer.h"
#include "nodes/coloredcube.h"
#include <QDebug>

static const QLatin1String KEY_CAMERA("camera");
static const QLatin1String KEY_CAMERA_EYE("eye");
static const QLatin1String KEY_CAMERA_CENTER("center");
static const QLatin1String KEY_CAMERA_UP("up");
static const QLatin1String KEY_OBJECTS("objects");
static const QLatin1String KEY_OBJECT_SCALE("scale");
static const QLatin1String KEY_OBJECT_POSITION("position");

SceneDeserializer::SceneDeserializer(const QString &filepath)
    : m_filepath(filepath)
{
}

SceneDeserializer::~SceneDeserializer()
{
}

bool SceneDeserializer::load(std::shared_ptr<BaseScene> scene)
{
    bool hasErrors = false;
    if (FILE *file = std::fopen(m_filepath.toLocal8Bit(), "r"))
    {
        try
        {
            QByteArray bytes;
            const size_t BUFFER_SIZE = 64 * 1024;
            char buffer[BUFFER_SIZE];
            while (size_t readCount = std::fread(buffer, sizeof(char), BUFFER_SIZE, file))
            {
                bytes.append(buffer, readCount);
            }

            QJsonParseError parseError;
            QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);
            if (parseError.error == QJsonParseError::NoError)
            {
                deserialize(document.object(), scene);
            }
            else
            {
                assert(!"load() failed: cannot parse JSON.");
                hasErrors = true;
            }
        }
        catch (...)
        {
            std::fclose(file);
            throw;
        }
        std::fclose(file);
    }
    else
    {
        assert(!"load() failed: cannot open file.");
        hasErrors = true;
    }
    return !hasErrors;
}

void SceneDeserializer::deserialize(const QJsonObject &source, std::shared_ptr<BaseScene> scene)
{
    QJsonObject cameraObj = source[KEY_CAMERA].toObject();
    QVector3D eyeVec    = parseVector3D(cameraObj[KEY_CAMERA_EYE].toArray());
    QVector3D centerVec = parseVector3D(cameraObj[KEY_CAMERA_CENTER].toArray());
    QVector3D upVec     = parseVector3D(cameraObj[KEY_CAMERA_UP].toArray());

    QJsonArray values = source[KEY_OBJECTS].toArray();
    for (QJsonValue const& value : values)
    {
        QJsonObject nodeObj = value.toObject();
        ColoredCube* cube = new ColoredCube(scene.get());
        cube->setScale(nodeObj[KEY_OBJECT_SCALE].toDouble());
        cube->setPosition(parseVector3D(nodeObj[KEY_OBJECT_POSITION].toArray()));
    }

    scene->camera().lookAt(eyeVec, centerVec, upVec);
}

QVector3D SceneDeserializer::parseVector3D(const QJsonArray &array) const
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
