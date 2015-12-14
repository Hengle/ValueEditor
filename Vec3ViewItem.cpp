#include "Vec3ViewItem.h"
#include "BaseViewItemCreator.h"
#include "ViewItemFactory.h"
#include <QtGui/QBoxLayout.h>
#include <QtGui/QLineEdit.h>
#include <assert.h>

Vec3ViewItem::Vec3ViewItem(
  QString const &name,
  QVariant const &value
  )
  : BaseViewItem( name )
  , m_vec3dValue( value.value<QVector3D>() )
{
  m_widget = new QWidget;

  m_xEdit = new QLineEdit( QString::number( m_vec3dValue.x() ), m_widget );
  m_yEdit = new QLineEdit( QString::number( m_vec3dValue.y() ), m_widget );
  m_zEdit = new QLineEdit( QString::number( m_vec3dValue.z() ), m_widget );

  // Connect em up.
  connect(
    m_xEdit, SIGNAL(editingFinished()),
    this, SLOT(onTextEditXChanged())
    );
  connect(
    m_yEdit, SIGNAL(editingFinished()),
    this, SLOT(onTextEditYChanged())
    );
  connect(
    m_zEdit, SIGNAL(editingFinished()),
    this, SLOT(onTextEditZChanged())
    );

  QHBoxLayout *layout = new QHBoxLayout( m_widget );
  layout->addWidget( m_xEdit );
  layout->addWidget( m_yEdit );
  layout->addWidget( m_zEdit );
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
  QVector3D newVec3dValue = value.value<QVector3D>();
  if ( newVec3dValue.x() != m_vec3dValue.x() )
    emit modelValueXChanged( QVariant( newVec3dValue.x() ) );
  if ( newVec3dValue.y() != m_vec3dValue.y() )
    emit modelValueYChanged( QVariant( newVec3dValue.y() ) );
  if ( newVec3dValue.z() != m_vec3dValue.z() )
    emit modelValueZChanged( QVariant( newVec3dValue.z() ) );
  m_vec3dValue = newVec3dValue;

  // Update our line edits
  m_xEdit->setText( QString::number(m_vec3dValue.x()) );
  m_yEdit->setText( QString::number(m_vec3dValue.y()) );
  m_zEdit->setText( QString::number(m_vec3dValue.z()) );
}

void Vec3ViewItem::onTextEditXChanged()
{
  QVector3D vec3d = m_vec3dValue;
  vec3d.setX( m_xEdit->text().toDouble() );
  emit ViewValueChanged( QVariant( vec3d ), GetName(), true );
}

void Vec3ViewItem::onTextEditYChanged()
{
  QVector3D vec3d = m_vec3dValue;
  vec3d.setY( m_yEdit->text().toDouble() );
  emit ViewValueChanged( QVariant( vec3d ), GetName(), true );
}

void Vec3ViewItem::onTextEditZChanged()
{
  QVector3D vec3d = m_vec3dValue;
  vec3d.setZ( m_zEdit->text().toDouble() );
  emit ViewValueChanged( QVariant( vec3d ), GetName(), true );
}

void Vec3ViewItem::onChildViewChanged(
  QVariant const &value,
  QString const &childName,
  bool commit
  )
{
  QVector3D vec3d = m_vec3dValue;

  if (childName == "X")
    vec3d.setX(value.toDouble());
  if (childName == "Y")
    vec3d.setY(value.toDouble());
  if (childName == "Z")
    vec3d.setZ(value.toDouble());

  emit ViewValueChanged( QVariant( vec3d ), GetName(), commit );
}

QList<BaseViewItem *> Vec3ViewItem::createChildViewItems() const
{
  ViewItemFactory* factory = ViewItemFactory::GetInstance();

  QList<BaseViewItem *> result;
  result.reserve( 3 );

  BaseViewItem *xChild = factory->CreateViewItem( "X", QVariant( m_vec3dValue.x() ) );
  connect(
    this, SIGNAL(modelValueXChanged(QVariant)),
    xChild, SLOT(UpdateViewValue(QVariant))
    );
  connect(
    xChild, SIGNAL(ViewValueChanged(QVariant, QString, bool)),
    this, SLOT(onChildViewChanged(QVariant, QString, bool))
    );
  result.append( xChild );

  BaseViewItem *yChild = factory->CreateViewItem( "Y", QVariant( m_vec3dValue.y() ) );
  connect(
    this, SIGNAL(modelValueYChanged(QVariant)),
    yChild, SLOT(UpdateViewValue(QVariant))
    );
  connect(
    yChild, SIGNAL(ViewValueChanged(QVariant, QString, bool)),
    this, SLOT(onChildViewChanged(QVariant, QString, bool))
    );
  result.append( yChild );

  BaseViewItem *zChild = factory->CreateViewItem( "Z", QVariant( m_vec3dValue.z() ) );
  connect(
    this, SIGNAL(modelValueZChanged(QVariant)),
    zChild, SLOT(UpdateViewValue(QVariant))
    );
  connect(
    zChild, SIGNAL(ViewValueChanged(QVariant, QString, bool)),
    this, SLOT(onChildViewChanged(QVariant, QString, bool))
    );
  result.append( zChild );

  return result;
}

//////////////////////////////////////////////////////////////////////////
// 
static Vec3ViewItem* CreateItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value,
  char const *tag
  )
{
  const int qv3Dtype = ((QVariant)QVector3D()).type();
  if (value.type() == qv3Dtype)
    return new Vec3ViewItem( name, value );
  else
    return nullptr;
}

EXPOSE_VIEW_ITEM( Vec3ViewItem, CreateItem, 3 );
