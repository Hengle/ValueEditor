#include "Vec3ViewItem.h"
#include "BaseViewItemCreator.h"
#include "ViewItemFactory.h"
#include <QtGui/QBoxLayout.h>
#include <QtGui/QLineEdit.h>
#include <QVector3D.h>

Vec3ViewItem::Vec3ViewItem(
  QString const &name
  )
  : BaseViewItem( name )
  , m_widget( new QWidget )
  , m_layout( new QHBoxLayout( m_widget ) )
  , m_xEdit( new QLineEdit( m_widget ) )
  , m_yEdit( new QLineEdit( m_widget ) )
  , m_zEdit( new QLineEdit( m_widget ) )
{
  QObject *widgetObject = m_widget;
  widgetObject->setParent( this );

  m_layout->addWidget( m_xEdit );
  m_layout->addWidget( m_yEdit );
  m_layout->addWidget( m_zEdit );

  // Connect em up.
  connect(
    m_xEdit, SIGNAL(textEdited(QString)),
    this, SLOT(OnTextEditsChanged())
    );
  connect(
    m_yEdit, SIGNAL(textEdited(QString)),
    this, SLOT(OnTextEditsChanged())
    );
  connect(
    m_zEdit, SIGNAL(textEdited(QString)),
    this, SLOT(OnTextEditsChanged())
    );
}

Vec3ViewItem::~Vec3ViewItem()
{
}

QWidget *Vec3ViewItem::getWidget()
{
  return m_widget;
}

void Vec3ViewItem::UpdateViewValue( QVariant value )
{
  m_value = value;

  // Update our line edits
  QVector3D vec = value.value<QVector3D>();
  m_xEdit->setText( QString::number(vec.x()) );
  m_yEdit->setText( QString::number(vec.y()) );
  m_zEdit->setText( QString::number(vec.z()) );

  GetChild(0)->UpdateViewValue( QVariant(vec.x()) );
  GetChild(1)->UpdateViewValue( QVariant(vec.y()) );
  GetChild(2)->UpdateViewValue( QVariant(vec.z()) );
}

void Vec3ViewItem::OnTextEditsChanged()
{
  QVector3D vec;
  vec.setX(m_xEdit->text().toDouble());
  vec.setY(m_yEdit->text().toDouble());
  vec.setZ(m_zEdit->text().toDouble());

  emit ViewValueChanged( QVariant( vec ), GetName(), true );
}

void Vec3ViewItem::onChildViewChanged(
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

  emit ViewValueChanged( QVariant( vec ), GetName(), commit );
}

//////////////////////////////////////////////////////////////////////////
// 
static Vec3ViewItem* CreateItem( const QVariant& data, const QString& name, const char* tag )
{
  const int qv3Dtype = ((QVariant)QVector3D()).type();
  if (data.type() == qv3Dtype)
  {
    Vec3ViewItem* pVec3ViewItem = new Vec3ViewItem( name );
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
