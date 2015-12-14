#include "BaseModelItem.h"
#include "DefaultViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QLabel.h>

DefaultViewItem::DefaultViewItem( BaseModelItem *modelItem )
  : BaseViewItem( modelItem->GetName() )
  , m_modelItem( modelItem )
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
static BaseViewItem* CreateItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value,
  char const *tag
  )
{
  if ( modelItem )
    return new DefaultViewItem( modelItem );
  else
    return 0;
}

EXPOSE_VIEW_ITEM(DefaultViewItem, CreateItem, 0);
