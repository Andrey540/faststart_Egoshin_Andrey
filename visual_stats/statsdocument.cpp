#include "statsdocument.h"
#include "istatsmodelprovider.h"
#include "statsserializer.h"
#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>

namespace
{
const QLatin1String FILE_FORMAT_FILTER("*.json");
}

StatsDocument::StatsDocument(QWidget *parent, IStatsModelProvider &provider)
    : QObject(parent)
    , m_provider(provider)
{

}

void StatsDocument::createNew()
{
    StatsKeyValueModel model;
    m_provider.setStatsModel(model);
    m_path.clear();
    m_statsModel = model;
}

bool StatsDocument::open()
{
    QString openPath = selectOpenPath();
    if (openPath.isEmpty())
    {
        return false;
    }

    StatsKeyValueModel model;
    StatsSerializer serializer(openPath);
    if (!serializer.load(model))
    {
        return false;
    }    
    m_provider.setStatsModel(model);
    m_statsModel = m_provider.statsModel();
    m_path = openPath;
    return true;
}

bool StatsDocument::save()
{
    if (m_path.isEmpty())
    {
        return saveAs();
    }
    return saveByPath(m_path);
}

bool StatsDocument::saveAs()
{
    QString savePath = selectSavePath();
    return saveByPath(savePath);
}

bool StatsDocument::isModelChanged() const
{
    return m_statsModel != m_provider.statsModel();
}

bool StatsDocument::saveByPath(const QString &savePath)
{
    if (savePath.isEmpty())
    {
        return false;
    }
    StatsSerializer serializer(savePath);
    if (serializer.save(m_provider.statsModel()))
    {
        m_path = savePath;
        m_statsModel = m_provider.statsModel();
        return true;
    }
    return false;
}

QString StatsDocument::selectSavePath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getSaveFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}

QString StatsDocument::selectOpenPath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getOpenFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}
