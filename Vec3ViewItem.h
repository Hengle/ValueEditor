#pragma once

#pragma once

#include "BaseViewItem.h"
#include <QtGui/QLineEdit.h>

class Vec3ViewItem : public BaseViewItem
{
	Q_OBJECT

private:
	// WE cache the value, and print it out.  This is so if this class is
	// used for something it should not be, it will at least be printed
	// out (and we can see what type it should be).
	QVariant m_value;

	// Cache widgets
	QWidget* m_BaseW;
	QLineEdit* m_xEdit;
	QLineEdit* m_yEdit;
	QLineEdit* m_zEdit;
public:

	Vec3ViewItem(const QVariant& value, const QString& name);
	~Vec3ViewItem();

	QWidget* BuildWidgets(bool expanded) /*override*/;
	QVariant GetValue() /*override*/;

	void UpdateViewValue(QVariant value) /*override*/;
	
	virtual void onChildChanged(
		QVariant const &value,
		QString const &childName,
		bool commit
		) /*override*/;

public slots:

	void OnTextEditsChanged();

};
