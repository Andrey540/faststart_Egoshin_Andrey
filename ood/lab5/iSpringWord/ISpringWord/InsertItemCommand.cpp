#include "stdafx.h"
#include "InsertItemCommand.h"

CInsertItemCommand::CInsertItemCommand(std::deque<std::shared_ptr<CDocumentItem>> & items, std::shared_ptr<CDocumentItem> item,
	boost::optional<size_t> position)
	: m_items(items),
	  m_item(item),
	  m_position(position)
{}

void CInsertItemCommand::DoExecute()
{
	auto position = (m_position == boost::none) ? m_items.end() : m_items.begin() + *m_position;
	m_items.insert(position, m_item);
}
void CInsertItemCommand::DoUnexecute()
{
	auto position = (m_position != boost::none) ? m_items.begin() + *m_position : --m_items.end();
	m_items.erase(position);
}
