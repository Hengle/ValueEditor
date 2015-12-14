#include "RTValViewItemCreator.h"
#include "RTValViewItem.h"
#include "ViewItemFactory.h"

RTValViewItemCreator::RTValViewItemCreator()
{
}

RTValViewItemCreator::~RTValViewItemCreator()
{
}

BaseViewItem* RTValViewItemCreator::CreateItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value,
  char const *tag
  )
{
	if (value.type() != QVariant::UserType)
		return 0;
	if (value.userType() == qMetaTypeId<FabricCore::RTVal>())
		return 0;

	FabricCore::RTVal rtVal = value.value<FabricCore::RTVal>();
	const char* ctype = rtVal.getTypeNameCStr();

	if (rtVal.isObject() || rtVal.isStruct())
	{
		RTValViewItem* pViewItem = new RTValViewItem(QString(name));

		FabricCore::RTVal desc = rtVal.getDesc();
		const char* cdesc = desc.getStringCString();
		// TODO: parse cdesc, Build children from desc.

		// For thinking, assume 2 children, name "X", "Y"
		FabricCore::RTVal xval = rtVal.maybeGetMemberRef("X");
		QVariant xvariant = QVariant::fromValue<FabricCore::RTVal>(xval);
		BaseViewItem* pxChild = ViewItemFactory::GetInstance()->CreateViewItem( "X", xvariant );
		pViewItem->AddChild(pxChild);

		FabricCore::RTVal yval = rtVal.maybeGetMemberRef("Y");
		QVariant yvariant = QVariant::fromValue<FabricCore::RTVal>(yval);
		BaseViewItem* pyChild = ViewItemFactory::GetInstance()->CreateViewItem( "Y", yvariant );
		pViewItem->AddChild(pyChild);

		return pViewItem;
	}

	return 0;
}
