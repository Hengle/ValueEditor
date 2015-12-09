#pragma once

#include "BaseViewItemCreator.h"

class FloatViewItemCreator : public BaseViewItemCreator
{
	FloatViewItemCreator();
	~FloatViewItemCreator();

	virtual bool Matches(QVariant data, const char* type, const char* tag) override;

	virtual BaseViewItem* CreateItem(const QVariant& data, const char* type, const char* tag) override;

	virtual void DeleteThis() override;

};