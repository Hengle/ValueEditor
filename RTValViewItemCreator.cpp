#include "RTValViewItemCreator.h"
#include "RTValViewItem.h"
#include "ViewItemFactory.h"

RTValViewItemCreator::RTValViewItemCreator()
{

}

bool RTValViewItemCreator::Matches(QVariant data, const char* type, const char* tag)
{
	return false;
}

BaseViewItem* RTValViewItemCreator::CreateItem(const QVariant& data, const char* type, const char* tag)
{
	if (data.userType() != qMetaTypeId<FabricCore::RTVal>())
	{
		FabricCore::RTVal val = data.value<FabricCore::RTVal>();
		const char* ctype = val.getTypeNameCStr();

		if (val.isObject() || val.isStruct())
		{
			RTValViewItem* pViewItem = new RTValViewItem(QString(type));

			FabricCore::RTVal desc = val.getDesc();
			const char* cdesc = desc.getStringCString();
			// TODO: parse cdesc, Build children from desc.

			// For thinking, assume 2 children, name "X", "Y"
			FabricCore::RTVal xval = val.maybeGetMemberRef("X");
			QVariant xvariant = QVariant::fromValue<FabricCore::RTVal>(xval);
			BaseViewItem* pxChild = ViewItemFactory::GetInstance()->CreateViewItem(xvariant, "X");
			pViewItem->AddChild(pxChild);

			FabricCore::RTVal yval = val.maybeGetMemberRef("Y");
			QVariant yvariant = QVariant::fromValue<FabricCore::RTVal>(yval);
			BaseViewItem* pyChild = ViewItemFactory::GetInstance()->CreateViewItem(xvariant, "Y");
			pViewItem->AddChild(pyChild);

			return pViewItem;
		}
	}

	return nullptr;
}

void RTValViewItemCreator::DeleteThis()
{
	delete this;
}
