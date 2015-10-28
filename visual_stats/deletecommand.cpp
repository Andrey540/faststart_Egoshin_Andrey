#include "deletecommand.h"

DeleteCommand::DeleteCommand(std::shared_ptr<StatsTableModel> tableModel, int row)
    : m_tableModel(tableModel),
      m_row(row)
{
}

void DeleteCommand::undo()
{
    auto model = m_tableModel->statsModel();
    model.insert(m_row, m_text, m_value);
    m_tableModel->setStatsModel(model);
}

void DeleteCommand::redo()
{
    auto statsModel = m_tableModel->statsModel();
    StatsKeyValueModel newModel;
    for (int i = 0, n = statsModel.size(); i < n; ++i)
    {
        if (m_row == i)
        {
            m_text = statsModel.key(i);
            m_value = statsModel.value(i);
            continue;
        }
        newModel.append(statsModel.key(i), statsModel.value(i));
    }
    m_tableModel->setStatsModel(newModel);
}
