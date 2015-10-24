#ifndef EDITCOMMAND_H
#define EDITCOMMAND_H

#include "statstablemodel.h"
#include <QString>
#include <QUndoCommand>

class EditCommand : public QUndoCommand
{
public:
    EditCommand(std::shared_ptr<StatsTableModel> tableModel, int row, QString key, int value);
    virtual void undo();
    virtual void redo();

private:
    std::shared_ptr<StatsTableModel> m_tableModel;
    int m_row;
    QString m_key;
    int m_value;
    int m_oldValue;
    QString m_oldKey;
};

#endif // EDITCOMMAND_H
