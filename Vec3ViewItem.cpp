#include "Vec3ViewItem.h"

Vec3ViewItem::Vec3ViewItem(const QVariant& value, const QString& name)
	: BaseViewItem(name)
	, m_value(value)
	, m_xEdit(nullptr)
	, m_yEdit(nullptr)
	, m_zEdit(nullptr)
	, m_BaseW(nullptr)
{

}

Vec3ViewItem::~Vec3ViewItem()
{

}

QWidget* Vec3ViewItem::BuildWidgets(bool /*expanded*/)
{
	if (m_BaseW == nullptr)
	{
		// Layout 3 edit boxes horizontally
		m_BaseW = new QWidget;
		QHBoxLayout *layout = new QHBoxLayout(m_BaseW);

		// Create XYZ edit boxes
		m_xEdit = new QLineEdit(m_BaseW);
		m_yEdit = new QLineEdit(m_BaseW);
		m_zEdit = new QLineEdit(m_BaseW);

		// Connect em up.
		connect(m_xEdit, SIGNAL(textEdited(QString)),
				this, SLOT(OnTextEditsChanged()));
		connect(m_yEdit, SIGNAL(textEdited(QString)),
				this, SLOT(OnTextEditsChanged()));
		connect(m_zEdit, SIGNAL(textEdited(QString)),
				this, SLOT(OnTextEditsChanged()));

		layout->addWidget(m_xEdit);
		layout->addWidget(m_yEdit);
		layout->addWidget(m_zEdit);

		UpdateViewValue(m_value);
	}
	return m_BaseW;
}

QVariant Vec3ViewItem::GetValue()
{
	return m_value;
}

void Vec3ViewItem::UpdateViewValue(QVariant value)
{
	m_value = value;

	// Update our line edits
	QVector3D vec = value.value<QVector3D>();
	if (m_xEdit != nullptr)
		m_xEdit->setText(QString::number(vec.x()));
	if (m_yEdit != nullptr)
		m_yEdit->setText(QString::number(vec.y()));
	if (m_zEdit != nullptr)
		m_zEdit->setText(QString::number(vec.z()));

	GetChild(0)->UpdateViewValue(QVariant(vec.x()));
	GetChild(1)->UpdateViewValue(QVariant(vec.y()));
	GetChild(2)->UpdateViewValue(QVariant(vec.z()));
}


void Vec3ViewItem::OnTextEditsChanged()
{
	QVector3D vec;
	if (m_xEdit != nullptr)
		vec.setX(m_xEdit->text().toDouble());
	if (m_yEdit != nullptr)
		vec.setY(m_yEdit->text().toDouble());
	if (m_zEdit != nullptr)
		vec.setZ(m_zEdit->text().toDouble());

	m_value = vec;
	emit ViewValueChanged(m_value, GetName(), true);
}

void Vec3ViewItem::OnChildChanged(QVariant value, QString childName, bool commit)
{
	// Assume m_value valid?
	QVector3D vec = m_value.value<QVector3D>();

	if (childName == "X")
		vec.setX(value.toDouble());
	if (childName == "Y")
		vec.setY(value.toDouble());
	if (childName == "Z")
		vec.setZ(value.toDouble());

	m_value = vec;
	emit ViewValueChanged(m_value, GetName(), commit);
}

#include "moc_Vec3ViewItem.cpp"