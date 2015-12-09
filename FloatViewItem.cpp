#include "FloatViewItem.h"
#include <QtGui/QDoubleSpinBox>

FloatViewItem::FloatViewItem(QString name)
	: m_spinner(nullptr)
	, BaseViewItem(name)
{

}

FloatViewItem::~FloatViewItem()
{
	if (m_spinner != nullptr)
		delete m_spinner;
}

QWidget * FloatViewItem::BuildWidgets(bool expanded)
{
	if (m_spinner != nullptr)
		return m_spinner;

	m_spinner = new QDoubleSpinBox();
	connect(m_spinner, SIGNAL(valueChanged(int)), this, SLOT(OnSpinnerChanged(int)));
	return m_spinner;
}

void FloatViewItem::UpdateValue(QVariant value)
{
	if (m_spinner != nullptr)
		m_spinner->setValue(value.toDouble());
}

QVariant FloatViewItem::GetValue()
{
	return QVariant::fromValue<double>(m_spinner->value());
}

void FloatViewItem::OnSpinnerChanged(double value)
{
	emit ValueChanged(QVariant(value), GetName());
}

#include "moc_FloatViewItem.cpp"