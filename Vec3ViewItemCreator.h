#pragma once
#pragma once

#include "BaseViewItemCreator.h"

class Vec3ViewItemCreator : public BaseViewItemCreator
{
	virtual BaseViewItem* CreateItem(const QVariant& data, const QString& name, const char* tag) override;
};