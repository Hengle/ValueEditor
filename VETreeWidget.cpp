#include "VETreeWidget.h"
#include "VETreeWidgetItem.h"
#include "BaseViewItem.h"
#include "BaseModelItem.h"
#include "ViewItemFactory.h"

VETreeWidget::VETreeWidget( )
{
  setColumnCount( 2 );
  connect(
    this, SIGNAL( itemExpanded( QTreeWidgetItem * ) ),
    this, SLOT( onTreeWidgetItemExpanded( QTreeWidgetItem * ) )
    );
  connect(
    this, SIGNAL( itemCollapsed( QTreeWidgetItem * ) ),
    this, SLOT( onTreeWidgetItemCollapsed( QTreeWidgetItem * ) )
    );
}

void VETreeWidget::createTreeWidgetItem( BaseViewItem* viewItem, QTreeWidgetItem* parentTreeWidgetItem, int index )
{
  assert( viewItem );
  if (viewItem == NULL)
    return;

  VETreeWidgetItem *treeWidgetItem = new VETreeWidgetItem( viewItem );
  if (viewItem->hasChildren())
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
  else
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicator );

  if (parentTreeWidgetItem)
  {
    if (index < 0 || index >= parentTreeWidgetItem->childCount())
      parentTreeWidgetItem->addChild( treeWidgetItem );
    else
      parentTreeWidgetItem->insertChild( index, treeWidgetItem );
  }
  else
    addTopLevelItem( treeWidgetItem );

  viewItem->setWidgetsOnTreeItem( this, treeWidgetItem );
}

VETreeWidgetItem * VETreeWidget::findTreeWidget( BaseModelItem * pItem ) const
{
  for (int i = 0; i < topLevelItemCount(); i++)
  {
    VETreeWidgetItem* widgetItem = 
      static_cast<VETreeWidgetItem*>(topLevelItem( i ));

    if (widgetItem != NULL)
    {
      VETreeWidgetItem* pMatch = findTreeWidget( pItem, widgetItem );
      if (pMatch != NULL)
        return pMatch;
    }
  }
  return NULL;
}

VETreeWidgetItem * VETreeWidget::findTreeWidget( BaseModelItem * pItem, VETreeWidgetItem * pWidget ) const
{
  if (pWidget == NULL)
    return NULL;

  BaseViewItem* pView = pWidget->getViewItem();
  if (pView != NULL && pView->GetModelItem() == pItem)
    return pWidget;
  
  for (int i = 0; i < pWidget->childCount(); i++)
  {
    VETreeWidgetItem* pMatch = findTreeWidget(
      pItem,
      static_cast<VETreeWidgetItem*>(pWidget->child( i )) );

    if (pMatch != NULL)
      return pMatch;
  }
  return NULL;
}

void VETreeWidget::onModelItemChildInserted( BaseModelItem* parent, int index, const char* name )
{
  QTreeWidgetItem* parentItem = findTreeWidget( parent );
  if (parent != NULL)
  {
    if (parentItem->isExpanded())
    {
      // Insert new child in the appropriate place
      BaseModelItem* newItem = parent->GetChild( index );
      assert( newItem->GetName() == name );
      BaseViewItem* newView = 
        ViewItemFactory::GetInstance()->CreateViewItem( newItem );
      createTreeWidgetItem( newView, parentItem, index );
    }
    else
      parentItem->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
  }
}

void VETreeWidget::onModelItemRemoved( BaseModelItem* item )
{
  VETreeWidgetItem* oldWidget = findTreeWidget( item );
  if (oldWidget != NULL)
    delete oldWidget;
}

void VETreeWidget::onModelItemTypeChanged( BaseModelItem* item, const char* newType )
{
  VETreeWidgetItem* oldWidget = findTreeWidget( item );
  if (oldWidget != NULL)
  {
    // We can get repeat messages for type changed, check
    // that its not actually the same type.  If we start
    // getting slow, checking type here would be a sensible
    // operation.
    //if (item->GetValue() == oldWidget->getViewItem()->)

    QTreeWidgetItem* parentItem = oldWidget->parent();
    if (parentItem != NULL)
    {
      int index = parentItem->indexOfChild( oldWidget );
      BaseViewItem* newView =
        ViewItemFactory::GetInstance()->CreateViewItem( item );
      createTreeWidgetItem( newView, parentItem, index );
    }
    delete oldWidget;
  }
}

void VETreeWidget::onModelItemChildrenReordered( BaseModelItem* parent, const QList<int>& newOrder )
{
  VETreeWidgetItem* parWidget = findTreeWidget( parent );
  if (parWidget != NULL && parWidget->isExpanded())
  {
    QList<QTreeWidgetItem*> oldChildren = parWidget->takeChildren();
    assert( oldChildren.size() == newOrder.size() );
    
    QList<QTreeWidgetItem*> children;
    children.reserve( newOrder.size() );
    for (int i = 0; i < newOrder.size(); i++)
      children.push_back( oldChildren[ newOrder[i] ] );
    
    // Reset children on widget
    parWidget->addChildren( children );
  }
}

void VETreeWidget::onSetModelItem( BaseModelItem* pItem )
{
  ViewItemFactory* pFactory = ViewItemFactory::GetInstance();
  BaseViewItem* pViewLayer = pFactory->BuildView( pItem );
  // Remove all existing
  clear();
  createTreeWidgetItem( pViewLayer, NULL );
}

void VETreeWidget::onTreeWidgetItemExpanded( QTreeWidgetItem *_treeWidgetItem )
{
  VETreeWidgetItem *treeWidgetItem =
    static_cast<VETreeWidgetItem *>( _treeWidgetItem );
  BaseViewItem *viewItem = treeWidgetItem->getViewItem();
  QList<BaseViewItem *> childViewItems;
  viewItem->appendChildViewItems( childViewItems );
  for ( int i = 0; i < childViewItems.size(); ++i )
  {
    BaseViewItem *childViewItem = childViewItems.at( i );
    createTreeWidgetItem( childViewItem, treeWidgetItem );
  }
}

void VETreeWidget::onTreeWidgetItemCollapsed( QTreeWidgetItem *treeWidgetItem )
{
  for ( int i = treeWidgetItem->childCount(); i--; )
  {
    VETreeWidgetItem *childTreeWidgetItem =
      static_cast<VETreeWidgetItem *>( treeWidgetItem->child( i ) );
    treeWidgetItem->removeChild( childTreeWidgetItem );
    delete childTreeWidgetItem;
  }
}
