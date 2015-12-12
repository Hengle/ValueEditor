#include "Vec3ViewItemCreator.h"
#include "Vec3ViewItem.h"
#include "ViewItemFactory.h"

BaseViewItem* Vec3ViewItemCreator::CreateItem(const QVariant& data, const QString& name, const char* /*tag*/)
{

	const int qv3Dtype = ((QVariant)QVector3D()).type();
	if (data.type() == qv3Dtype)
	{
		Vec3ViewItem* pVec3ViewItem = new Vec3ViewItem(data, name);
		QVector3D value = data.value<QVector3D>();
		// Add 3 float children as sub-controls
		ViewItemFactory* pFactory = ViewItemFactory::GetInstance();
		BaseViewItem* pxChild = pFactory->CreateViewItem(QVariant(value.x()), QString("X"));
		BaseViewItem* pyChild = pFactory->CreateViewItem(QVariant(value.y()), QString("Y"));
		BaseViewItem* pzChild = pFactory->CreateViewItem(QVariant(value.z()), QString("Z"));

		pVec3ViewItem->AddChild(pxChild, true);
		pVec3ViewItem->AddChild(pyChild, true);
		pVec3ViewItem->AddChild(pzChild, true);
		return pVec3ViewItem;
	}
	return nullptr;
}