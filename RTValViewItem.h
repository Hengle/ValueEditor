#pragma once

#include "BaseViewItem.h"
#include "QVariantRTVal.h"

class RTValViewItem : public BaseViewItem
{
	Q_OBJECT

	// Cache the val for easier reconstruction.  Why?  cause why not?
	FabricCore::RTVal m_val; 

	QWidget* m_parentWidget;

public:
	RTValViewItem(QString name);
	~RTValViewItem();

	virtual QWidget* BuildWidgets(bool expanded) /*override*/;

	virtual void UpdateViewValue(QVariant value) /*override*/;

	virtual QVariant GetValue() /*override*/;

	virtual void onChildViewChanged(
		QVariant const &value,
		QString const &name,
		bool commit
		) /*override*/;
};
