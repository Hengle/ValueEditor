#include "DefaultViewItemCreator.h"
#include "DefaultViewItem.h"

BaseViewItem* DefaultViewItemCreator::CreateItem(const QVariant& data, const QString& name, const char* tag)
{
	// We should not be created for actual genuine values.
	//assert(data.type() == QVariant::Invalid);
	return new DefaultViewItem(data, name);
}
