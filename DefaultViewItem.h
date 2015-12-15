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

	DefaultViewItem(
    BaseModelItem *modelItem,
    QString const &name,
    QVariant const &value
    );
	~DefaultViewItem();

	virtual QWidget *getWidget() /*override*/;

	virtual void onModelValueChanged( QVariant const &value ) /*override*/;

	virtual void onChildViewValueChanged(
    QVariant const &,
    QString const &,
    bool
    ) /*override*/
	  {}

  virtual bool hasChildren() const /*override*/;

  virtual QList<BaseViewItem *> createChildViewItems() const;
};
