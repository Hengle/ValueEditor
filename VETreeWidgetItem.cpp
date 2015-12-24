#include "VETreeWidgetItem.h"
#include "BaseViewItem.h"

VETreeWidgetItem::VETreeWidgetItem( BaseViewItem *viewItem ) : m_viewItem( viewItem )
{
  assert( viewItem );
}

VETreeWidgetItem::~VETreeWidgetItem()
{
  // We own this pointer, we need to release it.
  m_viewItem->deleteMe();
}

BaseViewItem * VETreeWidgetItem::getViewItem() const
{
  return m_viewItem;
}

