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

QTreeWidgetItem * VETreeWidget::findTreeWidget( BaseModelItem * pItem ) const
{
  for (int i = 0; i < topLevelItemCount(); i++)
  {
    VETreeWidgetItem* widgetItem = 
      static_cast<VETreeWidgetItem*>(topLevelItem( i ));

    if (widgetItem != NULL)
    {
      QTreeWidgetItem* pMatch = findTreeWidget( pItem, widgetItem );
      if (pMatch != NULL)
        return pMatch;
    }
  }
  return NULL;
}

QTreeWidgetItem * VETreeWidget::findTreeWidget( BaseModelItem * pItem, VETreeWidgetItem * pWidget ) const
{
  if (pWidget == NULL)
    return NULL;

  BaseViewItem* pView = pWidget->getViewItem();
  if (pView != NULL && pView->GetModelItem() == pItem)
    return pWidget;
  
  for (int i = 0; i < pWidget->childCount(); i++)
  {
    QTreeWidgetItem* pMatch = findTreeWidget(
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

}

void VETreeWidget::onModelItemTypeChanged( BaseModelItem* parent, const char* newType )
{
  assert( "IMPLEMENT THIS" );
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
