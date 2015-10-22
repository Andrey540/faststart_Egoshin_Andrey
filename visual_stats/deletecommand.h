#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include "statstablemodel.h"
#include <QString>
#include <QUndoCommand>

class DeleteCommand : public QUndoCommand
{
public:
    DeleteCommand(std::shared_ptr<StatsTableModel> tableModel, int row);
    virtual void undo();
    virtual void redo();

private:
    std::shared_ptr<StatsTableModel> m_tableModel;
    QString m_text;
    int m_value;
    int m_row;
};

#endif // DELETECOMMAND_H
