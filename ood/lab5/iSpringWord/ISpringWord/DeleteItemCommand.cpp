#include "stdafx.h"
#include "DeleteItemCommand.h"

CDeleteItemCommand::CDeleteItemCommand(std::deque<std::shared_ptr<CDocumentItem>> & items, size_t position)
	: m_items(items),
	m_position(position)
{}

void CDeleteItemCommand::DoExecute()
{
	m_item = *(m_items.begin() + m_position);
	m_items.erase(m_items.begin() + m_position);
}
void CDeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin() + m_position, m_item);
}