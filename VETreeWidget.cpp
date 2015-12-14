#include "VETreeWidget.h"
#include "BaseViewItem.h"

VETreeWidget::VETreeWidget( BaseViewItem *rootViewItem )
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
  rootViewItem->addToTreeWidget( this, 0 );
}

void VETreeWidget::onTreeWidgetItemExpanded( QTreeWidgetItem *_treeWidgetItem )
{
  BaseViewItem::TreeWidgetItem *treeWidgetItem =
    static_cast<BaseViewItem::TreeWidgetItem *>( _treeWidgetItem );
  BaseViewItem *viewItem = treeWidgetItem->getViewItem();
  QList<BaseViewItem *> childViewItems = viewItem->createChildViewItems();
  QTreeWidget *treeWidget = treeWidgetItem->treeWidget();
  for ( int i = 0; i < childViewItems.size(); ++i )
  {
    BaseViewItem *childViewItem = childViewItems.at( i );
    childViewItem->setParent( viewItem );
    childViewItem->addToTreeWidget( treeWidget, treeWidgetItem );
  }
}

void VETreeWidget::onTreeWidgetItemCollapsed( QTreeWidgetItem *_treeWidgetItem )
{
  BaseViewItem::TreeWidgetItem *treeWidgetItem =
    static_cast<BaseViewItem::TreeWidgetItem *>( _treeWidgetItem );
  BaseViewItem *viewItem = treeWidgetItem->getViewItem();
  for ( int i = treeWidgetItem->childCount(); i--; )
  {
    BaseViewItem::TreeWidgetItem *childTreeWidgetItem =
      static_cast<BaseViewItem::TreeWidgetItem *>( treeWidgetItem->child( i ) );
    treeWidgetItem->removeChild( childTreeWidgetItem );
    BaseViewItem *childViewItem = childTreeWidgetItem->getViewItem();
    delete childTreeWidgetItem;
    childViewItem->setParent( 0 );
    delete childViewItem;
  }
}
