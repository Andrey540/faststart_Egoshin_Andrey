#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <boost\optional.hpp>
#include <boost\none.hpp>

class CDeleteItemCommand :
	public CAbstractCommand
{
public:
public:
	CDeleteItemCommand(std::deque<std::shared_ptr<CDocumentItem>> & items, size_t position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::deque<std::shared_ptr<CDocumentItem>> & m_items;
	std::shared_ptr<CDocumentItem> m_item;
	size_t m_position;
};

