#include "gameapplication.h"
#include "scenedeserializer.h"
#include "gl/scenenode.h"
#include "nodes/coloredcube.h"
#include <QDebug>

const QSize FIXED_WINDOW_SIZE(800, 600);
const QString JSON_FILE_PATH = "/scene";

GameApplication::GameApplication(int argc, char *argv[])
    : QGuiApplication(argc, argv)
{
}

int GameApplication::enterGameLoop()
{
    m_window.setFixedSize(FIXED_WINDOW_SIZE);
    m_window.show();
    connect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    return exec();
}

void GameApplication::loadScene()
{
    disconnect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    if (!loadSceneFromJSON())
    {
        auto scene = std::make_shared<BaseScene>();
        scene->camera().setViewport(m_window.size());
        scene->camera().lookAt(QVector3D(3, 1, 1), QVector3D(0, 0, 0), QVector3D(0, 0, 1));
        new ColoredCube(scene.get());
        m_window.pushScene(scene);
    }
}

bool GameApplication::loadSceneFromJSON()
{
    auto scene = std::make_shared<BaseScene>();
    scene->camera().setViewport(m_window.size());
    SceneDeserializer deserializer(QCoreApplication::applicationDirPath() + JSON_FILE_PATH);
    if (!deserializer.load(scene))
    {
        return false;
    }
    m_window.pushScene(scene);

    return true;
}

