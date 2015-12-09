#include "ViewItemFactory.h"
#include "BaseViewItemCreator.h"

ViewItemFactory::ViewItemFactory()
{

}

ViewItemFactory::~ViewItemFactory()
{
	// destruct all remaining creators.
	while (!m_creators.empty())
		(*m_creators.rbegin())->DeleteThis();
}

ViewItemFactory* ViewItemFactory::GetInstance()
{
	static ViewItemFactory instance;
	return &instance;
}


bool ViewItemFactory::RegisterCreator(BaseViewItemCreator* creator)
{
	for (auto itr = m_creators.begin(); itr != m_creators.end(); itr++)
	{
		if (*itr == creator)
			return false;
	}
	m_creators.push_back(creator);
	return true;
}

void ViewItemFactory::DeRegisterCreator(BaseViewItemCreator* creator)
{
	for (auto itr = m_creators.begin(); itr != m_creators.end(); itr++)
	{
		if (*itr == creator)
		{
			m_creators.erase(itr);
			break;
		}
	}
}

BaseViewItem* ViewItemFactory::CreateViewItem(const QVariant& data, const char* viewtype, const char* tag)
{
	// iterate in reverse.  This ensures we test the most-specialized types
	// before testing the more generalized types
	for (auto itr = m_creators.rbegin(); itr != m_creators.rend(); itr++)
	{
		BaseViewItem* viewItem = (*itr)->CreateItem(data, viewtype, tag);
		if (viewItem != nullptr)
			return viewItem;
	}

	return nullptr;
}

