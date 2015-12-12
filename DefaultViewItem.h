#pragma once

#include "BaseViewItem.h"

class DefaultViewItem : public BaseViewItem
{
private:
	// WE cache the value, and print it out.  This is so if this class is
	// used for something it should not be, it will at least be printed
	// out (and we can see what type it should be).
	QVariant m_value;

public:

	DefaultViewItem(const QVariant& value, const QString& name);
	~DefaultViewItem();

	QWidget* BuildWidgets(bool expanded) override;

	QVariant GetValue() override;

	void UpdateViewValue(QVariant value) override;
	void OnChildChanged(QVariant, QString, bool) override {};
};