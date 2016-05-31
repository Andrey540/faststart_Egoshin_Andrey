#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <boost\optional.hpp>
#include <boost\none.hpp>

class CInsertItemCommand :
	public CAbstractCommand
{
public:
	CInsertItemCommand(std::deque<std::shared_ptr<CDocumentItem>> & items, std::shared_ptr<CDocumentItem> item,
		boost::optional<size_t> position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::deque<std::shared_ptr<CDocumentItem>> & m_items;
	std::shared_ptr<CDocumentItem> m_item;
	boost::optional<size_t> m_position;
};

