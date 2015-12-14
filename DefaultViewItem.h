#pragma once

#include "BaseViewItem.h"
#include <QtGui/QLabel.h>

class DefaultViewItem : public BaseViewItem
{
private:
	
  QLabel *m_label;

public:

	DefaultViewItem( const QVariant& value, const QString& name );
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
