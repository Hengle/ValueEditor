#pragma once
#include "BaseViewItemCreator.h"

class RTValViewItemCreator : public BaseViewItemCreator
{
public:
	RTValViewItemCreator();
	~RTValViewItemCreator();

	virtual BaseViewItem* CreateItem(
    BaseModelItem *modelItem,
    QString const &name,
    QVariant const &value,
    char const *tag
    ) /*override*/;
};
