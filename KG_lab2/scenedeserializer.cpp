#include "scenedeserializer.h"
#include "parseutils.h"
#include "nodes/coloredcube.h"
#include "nodes/shadedcube.h"
#include "nodes/coloredtetrahedron.h"
#include <QDebug>

static const QLatin1String KEY_CAMERA("camera");
static const QLatin1String KEY_CAMERA_EYE("eye");
static const QLatin1String KEY_CAMERA_CENTER("center");
static const QLatin1String KEY_CAMERA_UP("up");
static const QLatin1String KEY_OBJECTS("objects");
static const QLatin1String KEY_CLASS("class");

static const QString COLOREDCUBE("ColoredCube");
static const QString SHADEDCUBE("ShadedCube");
static const QString COLOREDTETRAHEDRON("ColoredTetrahedron");

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
    QVector3D eyeVec    = ParseUtils::parseVector3D(cameraObj[KEY_CAMERA_EYE].toArray());
    QVector3D centerVec = ParseUtils::parseVector3D(cameraObj[KEY_CAMERA_CENTER].toArray());
    QVector3D upVec     = ParseUtils::parseVector3D(cameraObj[KEY_CAMERA_UP].toArray());

    QJsonArray values = source[KEY_OBJECTS].toArray();
    for (QJsonValue const& value : values)
    {
        QJsonObject nodeObj = value.toObject();
        QString nodeClass = nodeObj[KEY_CLASS].toString();

        ILoadableNode* node;
        if (nodeClass == COLOREDCUBE)
        {
            node = new ColoredCube(scene.get());
        }
        else if (nodeClass == SHADEDCUBE)
        {
            node = new ShadedCube(scene.get());
        }
        else if (nodeClass == COLOREDTETRAHEDRON)
        {
            node = new ColoredTetrahedron(scene.get());
        }
        else
        {
            assert(!"Undefined node class");
        }
        node->load(nodeObj);
    }
    scene->camera().lookAt(eyeVec, centerVec, upVec);
}
