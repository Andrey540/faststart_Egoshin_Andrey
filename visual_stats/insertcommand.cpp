#include "insertcommand.h"

InsertCommand::InsertCommand(std::shared_ptr<StatsTableModel> tableModel,QString text, int value)
    : m_tableModel(tableModel),
      m_text(text),
      m_value(value)
{}

void InsertCommand::undo()
{
    auto statsModel = m_tableModel->statsModel();
    StatsKeyValueModel newModel;
    for (size_t i = 0, n = statsModel.size(); i < n; ++i)
    {
        if (statsModel.key(i) == m_text && statsModel.value(i) == m_value)
        {
            continue;
        }
        newModel.append(statsModel.key(i), statsModel.value(i));
    }
    m_tableModel->setStatsModel(newModel);
}

void InsertCommand::redo()
{
    auto model = m_tableModel->statsModel();
    model.append(m_text, m_value);
    m_tableModel->setStatsModel(model);
}
