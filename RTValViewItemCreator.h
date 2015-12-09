#pragma once
#include "BaseViewItemCreator.h"

class RTValViewItemCreator : public BaseViewItemCreator
{
	RTValViewItemCreator();
	~RTValViewItemCreator();

	virtual bool Matches(QVariant data, const char* type, const char* tag) override;

	virtual BaseViewItem* CreateItem(const QVariant& data, const char* type, const char* tag) override;

	virtual void DeleteThis() override;

};