#pragma once
#include "BaseViewItemCreator.h"

class RTValViewItemCreator : public BaseViewItemCreator
{
public:
	RTValViewItemCreator();
	~RTValViewItemCreator();

	virtual BaseViewItem* CreateItem(const QVariant& data, const QString& name, const char* tag) override;
};

#include "moc_BaseViewItem.cpp"