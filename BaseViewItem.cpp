#include "BaseViewItem.h"
#include "BaseModelItem.h"
#include <assert.h>
#include <QtGui/QTreeWidget.h>
#include "ViewItemFactory.h"

BaseViewItem::BaseViewItem( QString const &name )
  : m_name( name )
{
}


BaseViewItem::~BaseViewItem()
{
}

bool BaseViewItem::hasChildren() const
{
  if ( !!m_modelItem )
    return m_modelItem->NumChildren() > 0;
  return false;
}

void BaseViewItem::appendChildViewItems( QList<BaseViewItem *>& items )
{
  if ( !!m_modelItem )
  {
    ViewItemFactory *viewItemFactory = ViewItemFactory::GetInstance();

    size_t numChildren = m_modelItem->NumChildren();
    for (int i = 0; i < numChildren; ++i)
    {
      BaseModelItem *childModelItem = m_modelItem->GetChild( i );
      items.append( viewItemFactory->BuildView( childModelItem ) );
    }
  }
}

void BaseViewItem::setWidgetsOnTreeItem(
  QTreeWidget *treeWidget,
  QTreeWidgetItem *treeWidgetItem
  )
{
  treeWidgetItem->setText( 0, m_name );
  treeWidget->setItemWidget( treeWidgetItem, 1, getWidget() );
}
