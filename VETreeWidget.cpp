#include "VETreeWidget.h"
#include "VETreeWidgetItem.h"
#include "BaseViewItem.h"

VETreeWidget::VETreeWidget( BaseViewItem *rootViewItem )
{
  rootViewItem->setParent( this );
  setColumnCount( 2 );
  connect(
    this, SIGNAL( itemExpanded( QTreeWidgetItem * ) ),
    this, SLOT( onTreeWidgetItemExpanded( QTreeWidgetItem * ) )
    );
  connect(
    this, SIGNAL( itemCollapsed( QTreeWidgetItem * ) ),
    this, SLOT( onTreeWidgetItemCollapsed( QTreeWidgetItem * ) )
    );

  createTreeWidgetItem( rootViewItem, NULL );
}

void VETreeWidget::createTreeWidgetItem( BaseViewItem* viewItem, QTreeWidgetItem* parentTreeWidgetItem )
{
  VETreeWidgetItem *treeWidgetItem = new VETreeWidgetItem( viewItem );
  if (viewItem->hasChildren())
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
  else
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicator );

  viewItem->setWidgetsOnTreeItem( this, treeWidgetItem );
  if (parentTreeWidgetItem)
    parentTreeWidgetItem->addChild( treeWidgetItem );
  else
    addTopLevelItem( treeWidgetItem );
}
void VETreeWidget::onTreeWidgetItemExpanded( QTreeWidgetItem *_treeWidgetItem )
{
  VETreeWidgetItem *treeWidgetItem =
    static_cast<VETreeWidgetItem *>( _treeWidgetItem );
  BaseViewItem *viewItem = treeWidgetItem->getViewItem();
  QList<BaseViewItem *> childViewItems = viewItem->createChildViewItems();
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
