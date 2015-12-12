
#include "FloatViewItemCreator.h"
#include "FloatViewItem.h"

FloatViewItemCreator::FloatViewItemCreator()
{

}

FloatViewItemCreator::~FloatViewItemCreator()
{

}

bool FloatViewItemCreator::Matches(QVariant data, const char* /*type*/, const char* /*tag*/)
{
	return data.type() == QVariant::Double;// || data.type() == RTVal && data.asRTVal().getType() == "Scalar";
}

BaseViewItem* FloatViewItemCreator::CreateItem(const QVariant& /*data*/, const char* type, const char* /*tag*/)
{
	return new FloatViewItem(type);
}

void FloatViewItemCreator::DeleteThis()
{
	delete this;
}
