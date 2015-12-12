#pragma once

#include "BaseViewItemCreator.h"

class DefaultViewItemCreator : public BaseViewItemCreator
{
	virtual BaseViewItem* CreateItem(const QVariant& data, const QString& name, const char* tag) override;
};