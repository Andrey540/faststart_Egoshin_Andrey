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
    m_tableModel->setRowData(m_row, m_oldKey, m_oldValue);
}

void EditCommand::redo()
{
    auto statsModel = m_tableModel->statsModel();
    m_oldValue = statsModel.value(m_row);
    m_oldKey = statsModel.key(m_row);

    m_tableModel->setRowData(m_row, m_key, m_value);
}
