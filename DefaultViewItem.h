#pragma once

#include "BaseViewItem.h"

class BaseModelItem;
class QLabel;

class DefaultViewItem : public BaseViewItem
{
private:
	
  BaseModelItem *m_modelItem;
  QLabel *m_label;

public:

	DefaultViewItem( BaseModelItem *modelItem );
	~DefaultViewItem();

	virtual QWidget *getWidget() /*override*/;

	void UpdateViewValue( QVariant value ) /*override*/;

	virtual void onChildViewChanged(
    QVariant const &,
    QString const &,
    bool
    ) /*override*/
	  {}
};
