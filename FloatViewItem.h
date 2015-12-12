#pragma once
#include "BaseViewItem.h"

class QDoubleSpinBox;

class FloatViewItem : public BaseViewItem
{
	Q_OBJECT
public:
	FloatViewItem(QString name);
	~FloatViewItem();

	size_t NumChildren() override { return 0; }
	BaseViewItem* GetChild(size_t /*index*/) override { return nullptr; };

	QWidget* BuildWidgets(bool expanded) override;

	void UpdateViewValue(QVariant value) override;

	QVariant GetValue();

private:

	QDoubleSpinBox* m_spinner;

private slots:
	void OnSpinnerChanged(double value);
};