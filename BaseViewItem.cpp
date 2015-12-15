#include "BaseViewItem.h"
#include "BaseModelItem.h"


BaseViewItem::BaseViewItem( QString const &name )
  : m_name( name )
{
}


BaseViewItem::~BaseViewItem()
{
}

void BaseViewItem::onChildViewValueChanged(
  QVariant const &,
  QString const &,
  bool
  )
{
  /* default is no-op */
}

QList<BaseViewItem *> BaseViewItem::createChildViewItems() const
{
  return QList<BaseViewItem *>();
}

void BaseViewItem::addToTreeWidget(
  QTreeWidget *treeWidget,
  TreeWidgetItem *parentTreeWidgetItem
  )
{
  TreeWidgetItem *treeWidgetItem = new TreeWidgetItem( this );
  if ( hasChildren() )
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::ShowIndicator );
  else
    treeWidgetItem->setChildIndicatorPolicy( QTreeWidgetItem::DontShowIndicator );
  treeWidgetItem->setText( 0, m_name );
  if ( parentTreeWidgetItem )
    parentTreeWidgetItem->addChild( treeWidgetItem );
  else
    treeWidget->addTopLevelItem( treeWidgetItem );
  treeWidget->setItemWidget( treeWidgetItem, 1, getWidget() );
}
