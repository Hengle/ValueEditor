#include "BaseViewItem.h"
#include "BaseModelItem.h"
#include <assert.h>
#include <QtGui\QTreeWidget.h>
#include "ViewItemFactory.h"

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


bool BaseViewItem::hasChildren() const
{
  if (m_modelItem != nullptr)
    return m_modelItem->NumChildren() > 0;
  return false;
}

void BaseViewItem::appendChildViewItems( QList<BaseViewItem *>& items ) const
{
  if (m_modelItem)
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
