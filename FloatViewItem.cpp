#include "FloatViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QSpinBox.h>

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

QWidget * FloatViewItem::BuildWidgets(bool /*expanded*/)
{
  if (m_spinner != nullptr)
    return m_spinner;

  m_spinner = new QDoubleSpinBox();
  connect( m_spinner, SIGNAL( valueChanged( double ) ), 
       this, SLOT( OnSpinnerChanged( double ) ) );
  connect( m_spinner, SIGNAL( editingFinished() ), 
       this, SLOT( OnEditFinished() ) );

  return m_spinner;
}

void FloatViewItem::UpdateViewValue( QVariant value )
{
  if ( m_spinner != nullptr )
    m_spinner->setValue( value.toDouble() );
}

QVariant FloatViewItem::GetValue()
{
  return QVariant::fromValue<double>( m_spinner->value() );
}

void FloatViewItem::OnSpinnerChanged( double value )
{
  emit ViewValueChanged( QVariant( value ), GetName(), 0 );
}

void FloatViewItem::OnEditFinished()
{
  emit ViewValueChanged( QVariant( GetValue() ), GetName(), 1 );
}

//////////////////////////////////////////////////////////////////////////
// 
static FloatViewItem* CreateItem( const QVariant& data, const QString& name, const char* tag )
{
  if (data.type() == QVariant::Double || data.type() == QMetaType::Float)
  {
    return new FloatViewItem( name );
  }
  return nullptr;
}

EXPOSE_VIEW_ITEM( FloatViewItem, CreateItem, 3 );
