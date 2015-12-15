#include "RTValViewItem.h"
#include <QtGui/QWidget.h>

RTValViewItem::RTValViewItem(QString name)
	: BaseViewItem(name)
{
}

RTValViewItem::~RTValViewItem()
{
}

//size_t RTValViewItem::NumChildren()
//{
//	return m_children.size();
//}
//
//BaseViewItem* RTValViewItem::GetChild(size_t index)
//{
//	return m_children[index];
//}

QWidget *RTValViewItem::getWidget()
{
	return 0;
}

void RTValViewItem::onModelValueChanged( QVariant const &value )
{
	m_val = toRTVal( value );
	// for ( ChildIT itr = childBegin(); itr != childEnd(); itr++ )
	// {
	// 	QString childName = (*itr)->GetName();
	// 	QByteArray asciiName = childName.toAscii();
	// 	FabricCore::RTVal childVal = m_val.maybeGetMemberRef(asciiName.data());
	// 	// Assert childVal is valid
	// 	(*itr)->UpdateViewValue( toVariant(childVal) );
	// }
}

void RTValViewItem::onChildViewValueChanged(
	QVariant const &value,
	QString const &childName,
	bool commit
	)
{
	QByteArray asciiName = childName.toAscii();
	// We cannot simply create a new RTVal based on the QVariant type, as 
	// we have to set the type exactly the same as the original.  Get the
	// original child value to ensure the new value matches the internal type
	FabricCore::RTVal oldChildVal = m_val.maybeGetMemberRef(asciiName.data());
	VariantToRTVal(value, oldChildVal);
	m_val.setMember(asciiName.data(), oldChildVal);

	emit viewValueChanged( toVariant(m_val), commit );
}
