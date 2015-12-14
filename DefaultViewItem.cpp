#include "BaseModelItem.h"
#include "DefaultViewItem.h"
#include "BaseViewItemCreator.h"
#include "ViewItemFactory.h"
#include <QtGui/QLabel.h>

DefaultViewItem::DefaultViewItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value
  )
  : BaseViewItem( name )
  , m_modelItem( modelItem )
{
  m_label = new QLabel;

  UpdateViewValue( value );
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

bool DefaultViewItem::hasChildren() const
{
  if ( m_modelItem )
    return m_modelItem->NumChildren() > 0;
  else
    return 0;
}

QList<BaseViewItem *> DefaultViewItem::createChildViewItems() const
{
  QList<BaseViewItem *> result;
  if ( m_modelItem )
  {
    ViewItemFactory *viewItemFactory = ViewItemFactory::GetInstance();

    int numChildren = m_modelItem->NumChildren();
    result.reserve( numChildren );

    for ( int i = 0; i < numChildren; ++i )
    {
      BaseModelItem *childModelItem = m_modelItem->GetChild( i );
      result.append( viewItemFactory->BuildView( childModelItem ) );
    }
  }
  return result;
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
  return new DefaultViewItem( modelItem, name, value );
}

EXPOSE_VIEW_ITEM(DefaultViewItem, CreateItem, 0);
