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

void VETreeWidget::createTreeWidgetItem( BaseViewItem* viewItem, QTreeWidgetItem* parentTreeWidgetItem )
{
  VETreeWidgetItem *treeWidgetItem = new VETreeWidgetItem( viewItem );
  if (viewItem->hasChildren())
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
  else
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicator );

  if (parentTreeWidgetItem)
    parentTreeWidgetItem->addChild( treeWidgetItem );
  else
    addTopLevelItem( treeWidgetItem );

  viewItem->setWidgetsOnTreeItem( this, treeWidgetItem );
}

void VETreeWidget::onSetModelItem( BaseModelItem* pItem )
{
  ViewItemFactory* pFactory = ViewItemFactory::GetInstance();
  BaseViewItem* pViewLayer = pFactory->BuildView( pItem );

  clear();

  pViewLayer->setParent( this );
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
    childViewItem->setParent( viewItem );
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
    BaseViewItem *childViewItem = childTreeWidgetItem->getViewItem();
    delete childTreeWidgetItem;
    childViewItem->setParent( 0 );
    delete childViewItem;
  }
}
