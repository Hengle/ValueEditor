#pragma once
#include "BaseViewItem.h"

class QDoubleSpinBox;

class FloatViewItem : public BaseViewItem
{
	Q_OBJECT

public:

	FloatViewItem(QString name);
	~FloatViewItem();

	virtual QWidget *getWidget() /*override*/;
  
	void UpdateViewValue(QVariant value) /*override*/;

private:

	QDoubleSpinBox* m_spinner;

private slots:
	void OnSpinnerChanged(double value);
	void OnEditFinished();
};
