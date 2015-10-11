#pragma once

#include <QObject>
#include <memory>
#include "istatsmodelprovider.h"
#include "statskeyvaluemodel.h"

class QWidget;
class IStatsModelProvider;

class StatsDocument : public QObject
{
    Q_OBJECT
public:
    explicit StatsDocument(QWidget *parent, IStatsModelProvider &provider);

    void createNew();
    bool open();
    bool save();
    bool saveAs();
    bool isModelChanged() const;

private:
    bool saveByPath(const QString &savePath);    
    QString selectSavePath() const;
    QString selectOpenPath() const;

    IStatsModelProvider &m_provider;
    QString m_path;
    StatsKeyValueModel m_statsModel;
};
