#include "scenedeserializer.h"
#include "nodes/coloredcube.h"
#include "nodes/shadedcube.h"
#include "nodes/coloredtetrahedron.h"
#include "qjsonobjectwrapper.h"
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
    QJsonObjectWrapper cameraObjWrapper = QJsonObjectWrapper(source[KEY_CAMERA].toObject());
    QVector3D eyeVec    = cameraObjWrapper.getVector3D(KEY_CAMERA_EYE);
    QVector3D centerVec = cameraObjWrapper.getVector3D(KEY_CAMERA_CENTER);
    QVector3D upVec     = cameraObjWrapper.getVector3D(KEY_CAMERA_UP);

    QJsonArray values = source[KEY_OBJECTS].toArray();
    for (QJsonValue const& value : values)
    {
        QJsonObjectWrapper nodeObjWrapper = value.toObject();
        QString nodeClass = nodeObjWrapper.getString(KEY_CLASS);

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
        node->load(nodeObjWrapper);
    }
    scene->camera().lookAt(eyeVec, centerVec, upVec);
}
