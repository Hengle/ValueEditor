#include "FloatViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QSpinBox.h>

FloatViewItem::FloatViewItem(QString name)
  : BaseViewItem(name)
  , m_spinner( new QDoubleSpinBox )
{
  QObject *spinnerObject = m_spinner;
  spinnerObject->setParent( this );

  connect(
    m_spinner, SIGNAL( valueChanged( double ) ), 
    this, SLOT( OnSpinnerChanged( double ) )
    );
  connect(
    m_spinner, SIGNAL( editingFinished() ), 
    this, SLOT( OnEditFinished() )
    );
}

FloatViewItem::~FloatViewItem()
{
}

QWidget *FloatViewItem::getWidget()
{
  return m_spinner;
}

void FloatViewItem::UpdateViewValue( QVariant value )
{
  m_spinner->setValue( value.toDouble() );
}

void FloatViewItem::OnSpinnerChanged( double value )
{
  emit ViewValueChanged(
    QVariant::fromValue<double>( m_spinner->value() ),
    GetName(),
    0
    );
}

void FloatViewItem::OnEditFinished()
{
  emit ViewValueChanged(
    QVariant::fromValue<double>( m_spinner->value() ),
    GetName(),
    1
    );
}

//////////////////////////////////////////////////////////////////////////
// 
static FloatViewItem* CreateItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value,
  char const *tag
  )
{
  if ( value.type() == QVariant::Double
    || value.type() == QMetaType::Float )
  {
    return new FloatViewItem( name );
  }
  return nullptr;
}

EXPOSE_VIEW_ITEM( FloatViewItem, CreateItem, 3 );
