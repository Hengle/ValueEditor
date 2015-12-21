#include "RTValViewItem.h"
#include "BaseViewItemCreator.h"
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

//////////////////////////////////////////////////////////
//
static BaseViewItem* CreateItem(
  QString const &name,
  QVariant const &value,
  FTL::JSONObject* /*metaData*/
  )
{
  if (value.type() != QVariant::UserType)
    return NULL;
  if (value.userType() == qMetaTypeId<FabricCore::RTVal>())
    return NULL;

  FabricCore::RTVal rtVal = value.value<FabricCore::RTVal>();
  //const char* ctype = rtVal.getTypeNameCStr();

  if (rtVal.isObject() || rtVal.isStruct())
  {
    RTValViewItem* pViewItem = new RTValViewItem( QString( name ) );

    FabricCore::RTVal desc = rtVal.getDesc();
    //const char* cdesc = desc.getStringCString();
    // TODO: parse cdesc, Build children from desc.

   /* // For thinking, assume 2 children, name "X", "Y"
    FabricCore::RTVal xval = rtVal.maybeGetMemberRef( "X" );
    QVariant xvariant = QVariant::fromValue<FabricCore::RTVal>( xval );
    BaseViewItem* pxChild = ViewItemFactory::GetInstance()->CreateViewItem( "X", xvariant );
    // pViewItem->AddChild(pxChild);

    FabricCore::RTVal yval = rtVal.maybeGetMemberRef( "Y" );
    QVariant yvariant = QVariant::fromValue<FabricCore::RTVal>( yval );
    BaseViewItem* pyChild = ViewItemFactory::GetInstance()->CreateViewItem( "Y", yvariant );
    // pViewItem->AddChild(pyChild);
    */
    return pViewItem;
  }
  return NULL;
}

EXPOSE_VIEW_ITEM( RTValViewItem, CreateItem, 1 );
