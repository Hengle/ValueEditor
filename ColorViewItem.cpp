#include "ColorViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QLabel.h>

ColorViewItem::ColorViewItem( const QVariant& value, const QString& name )
  : BaseViewItem( name )
  , m_value( value )
{

}

ColorViewItem::~ColorViewItem()
{

}

QWidget* ColorViewItem::BuildWidgets( bool /*expanded*/ )
{
  if (m_value.canConvert( QVariant::String ))
  {
    QString string = m_value.toString();
    QLabel* label = new QLabel( string );
    return label;
  }
  return nullptr; // THe default view don't have no widgets
}

QVariant ColorViewItem::GetValue()
{
  return m_value;
}

void ColorViewItem::UpdateViewValue( QVariant value )
{
  m_value = value;
}

void ColorViewItem::onChildChanged( QVariant const &, QString const &, bool )
{

}

//////////////////////////////////////////////////////////////////////////
//

static ColorViewItem* CreateItem( const QVariant& data, const QString& name, const char* tag )
{
  return nullptr;
}
EXPOSE_VIEW_ITEM( ColorViewItem, CreateItem, 3 );
