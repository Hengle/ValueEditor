
#include "FloatViewItemCreator.h"
#include "FloatViewItem.h"

FloatViewItemCreator::FloatViewItemCreator()
{

}

FloatViewItemCreator::~FloatViewItemCreator()
{

}

BaseViewItem* FloatViewItemCreator::CreateItem(const QVariant& data, const QString& name, const char* /*tag*/)
{
	if (data.type() == QVariant::Double || data.type() == QMetaType::Float)
	{
		return new FloatViewItem(name);
	}
	return nullptr;
}
