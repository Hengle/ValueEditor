#include "Vec3ViewItem.h"
#include "BaseViewItemCreator.h"
#include "ViewItemFactory.h"
#include <QtGui/QBoxLayout.h>
#include <QtGui/QLineEdit.h>
#include <QVector3D.h>

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

void Vec3ViewItem::onChildChanged(
  QVariant const &value,
  QString const &childName,
  bool commit
  )
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

//////////////////////////////////////////////////////////////////////////
// 
static Vec3ViewItem* CreateItem( const QVariant& data, const QString& name, const char* tag )
{
  const int qv3Dtype = ((QVariant)QVector3D()).type();
  if (data.type() == qv3Dtype)
  {
    Vec3ViewItem* pVec3ViewItem = new Vec3ViewItem( data, name );
    QVector3D value = data.value<QVector3D>();
    // Add 3 float children as sub-controls
    ViewItemFactory* pFactory = ViewItemFactory::GetInstance();
    BaseViewItem* pxChild = pFactory->CreateViewItem( QVariant( value.x() ), QString( "X" ) );
    BaseViewItem* pyChild = pFactory->CreateViewItem( QVariant( value.y() ), QString( "Y" ) );
    BaseViewItem* pzChild = pFactory->CreateViewItem( QVariant( value.z() ), QString( "Z" ) );

    pVec3ViewItem->AddChild( pxChild, true );
    pVec3ViewItem->AddChild( pyChild, true );
    pVec3ViewItem->AddChild( pzChild, true );
    return pVec3ViewItem;
  }
  return nullptr;
}

EXPOSE_VIEW_ITEM( Vec3ViewItem, CreateItem, 3 );
