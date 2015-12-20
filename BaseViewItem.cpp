#include "BaseViewItem.h"
#include "BaseModelItem.h"
#include <assert.h>
#include <QtGui\QTreeWidget.h>

ViewItemChildRouter::ViewItemChildRouter(
  BaseViewItem *viewItem,
  int index
  )
  : m_viewItem( viewItem )
  , m_index( index )
{
  setParent( viewItem );
}

void ViewItemChildRouter::connectToChild( BaseViewItem *childViewItem )
{
  connect(
    this, SIGNAL(modelValueChanged(QVariant const &)),
    childViewItem, SLOT(onModelValueChanged(QVariant const &))
    );
  connect(
    childViewItem, SIGNAL(viewValueChanged(QVariant const &, bool)),
    this, SLOT(onViewValueChanged(QVariant const &, bool))
    );
}

void ViewItemChildRouter::emitModelValueChanged( QVariant const &value )
{
  emit modelValueChanged( value );
}

void ViewItemChildRouter::onViewValueChanged( QVariant const &value, bool commit )
{
  m_viewItem->onChildViewValueChanged( m_index, value, commit );
}

BaseViewItem::BaseViewItem( QString const &name )
  : m_name( name )
{
}


BaseViewItem::~BaseViewItem()
{
}

void BaseViewItem::onChildViewValueChanged(
  int /*index*/,
  QVariant const& /*value*/,
  bool /*commit*/
  )
{
  assert( false );
}

QList<BaseViewItem *> BaseViewItem::createChildViewItems() const
{
  return QList<BaseViewItem *>();
}

void BaseViewItem::setWidgetsOnTreeItem(
  QTreeWidget *treeWidget,
  QTreeWidgetItem *treeWidgetItem
  )
{
  treeWidgetItem->setText( 0, m_name );
  treeWidget->setItemWidget( treeWidgetItem, 1, getWidget() );
}
