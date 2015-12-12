#include "DefaultViewItem.h"

DefaultViewItem::DefaultViewItem(const QVariant& value, const QString& name)
	: BaseViewItem(name)
	, m_value(value)
{

}

DefaultViewItem::~DefaultViewItem()
{

}

QWidget* DefaultViewItem::BuildWidgets(bool /*expanded*/)
{
	if (m_value.canConvert(QVariant::String))
	{
		QString string = m_value.toString();
		QLabel* label = new QLabel(string);
		return label;
	}
	return nullptr; // THe default view don't have no widgets
}

QVariant DefaultViewItem::GetValue()
{
	return m_value;
}

void DefaultViewItem::UpdateViewValue(QVariant value)
{
	m_value = value;
}
