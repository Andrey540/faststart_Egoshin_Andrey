#include "editcommand.h"

EditCommand::EditCommand(std::shared_ptr<StatsTableModel> tableModel, int row, QString key, int value)
    : m_tableModel(tableModel),
      m_row(row),
      m_key(key),
      m_value(value)
{
}

void EditCommand::undo()
{
    auto model = m_tableModel->statsModel();
    model.setKey(m_row, m_oldKey);
    model.setValue(m_row, m_oldValue);
    m_tableModel->setStatsModel(model);
}

void EditCommand::redo()
{
    auto model = m_tableModel->statsModel();
    m_oldValue = model.value(m_row);
    m_oldKey = model.key(m_row);

    model.setKey(m_row, m_key);
    model.setValue(m_row, m_value);
    m_tableModel->setStatsModel(model);
}
