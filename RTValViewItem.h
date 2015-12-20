#pragma once

#include "BaseViewItem.h"
#include "QVariantRTVal.h"

class RTValViewItem : public BaseViewItem
{
	Q_OBJECT

	// Cache the val for easier reconstruction.  Why?  cause why not?
	FabricCore::RTVal m_val; 

	QWidget *m_widget;

public:

	RTValViewItem(QString name);
	~RTValViewItem();

	virtual QWidget *getWidget() /*override*/;

	virtual void onModelValueChanged( QVariant const &value ) /*override*/;

	virtual void onChildViewValueChanged(
		QVariant const &value,
		QString const &name,
		bool commit
		) /*override*/;

};
