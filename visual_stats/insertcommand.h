#ifndef INSERTCOMMAND_H
#define INSERTCOMMAND_H

#include "statstablemodel.h"
#include <QString>
#include <QUndoCommand>

class InsertCommand : public QUndoCommand
{
public:
    InsertCommand(std::shared_ptr<StatsTableModel> tableModel, QString text, int value);
    virtual void undo();
    virtual void redo();

private:
    std::shared_ptr<StatsTableModel> m_tableModel;
    QString m_text;
    int m_value;
};

#endif // INSERTCOMMAND_H
