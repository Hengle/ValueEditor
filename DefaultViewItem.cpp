#include "DefaultViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QLabel.h>

DefaultViewItem::DefaultViewItem(const QVariant& value, const QString& name)
  : BaseViewItem( name )
  , m_label( new QLabel )
{
  QObject *labelObject = m_label;
  labelObject->setParent( this );
}

DefaultViewItem::~DefaultViewItem()
{
}

QWidget *DefaultViewItem::getWidget()
{
  return m_label;
}

void DefaultViewItem::UpdateViewValue( QVariant value )
{
  if ( value.canConvert( QVariant::String ) )
  {
    QString string = value.toString();
    m_label->setText( string );
  }
}

//////////////////////////////////////////////////////////////////////////
// Expose the ViewItem to the UI layer
static BaseViewItem* CreateItem( const QVariant& data, const QString& name, const char* )
{
  return new DefaultViewItem( data, name );
}

EXPOSE_VIEW_ITEM(DefaultViewItem, CreateItem, 0);
