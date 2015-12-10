#include "RTValViewItem.h"
#include <QtGui\QTextEdit>
#include <QtGui\QtGui>

RTValViewItem::RTValViewItem(QString name)
	: BaseViewItem(name)
{

}

RTValViewItem::~RTValViewItem()
{

}

size_t RTValViewItem::NumChildren()
{
	return m_children.size();
}

BaseViewItem* RTValViewItem::GetChild(size_t index)
{
	return m_children[index];
}

QWidget* RTValViewItem::BuildWidgets(bool expanded)
{
	// Possible logic - if 3 or less children, who are all numeric, display values
	if (NumChildren() <= 3)
	{
		if (expanded)
		{
			QWidget *parentWidget = new QWidget();

			for (auto itr = m_children.begin(); itr != m_children.end(); itr++)
			{
				QLabel* label = new QLabel((*itr)->GetValue().toString());
			}
		}
	}
	return nullptr;
}

void RTValViewItem::UpdateValue(QVariant value)
{
	m_val = toRTVal(value);
	for (auto itr = m_children.begin(); itr != m_children.end(); itr++)
	{
		QString childName = (*itr)->GetName();
		QByteArray asciiName = childName.toAscii();
		FabricCore::RTVal childVal = m_val.maybeGetMemberRef(asciiName.data());
		// Assert childVal is valid
		(*itr)->UpdateValue(toVariant(childVal));
	}
}

void RTValViewItem::OnChildChanged(QVariant value, QString childName)
{
	QByteArray asciiName = childName.toAscii();
	// We cannot simply create a new RTVal based on the QVariant type, as 
	// we have to set the type exactly the same as the original.  Get the
	// original child value to ensure the new value matches the internal type
	FabricCore::RTVal oldChildVal = m_val.maybeGetMemberRef(asciiName.data());
	VariantToRTVal(m_client, value, oldChildVal);
	m_val.setMember(asciiName.data(), oldChildVal);

	emit OnValueChanged(toVariant(m_val), GetName());
}

QVariant RTValViewItem::GetValue()
{
	return toVariant(m_val);
}

void RTValViewItem::AddChild(BaseViewItem* pChild)
{
	m_children.push_back(pChild);

	connect(pChild, SIGNAL(ValueChanged(QVariant value, const QString& name)),
			this,	SLOT(OnChildChanged(QVariant value, const QString& name)));
}

#include "moc_RTValViewItem.cpp"