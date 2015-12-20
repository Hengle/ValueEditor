#pragma once

#include <QtGui/QTreeWidget.h>

class BaseViewItem;

class VETreeWidgetItem : public QTreeWidgetItem
{
public:

  VETreeWidgetItem( BaseViewItem *viewItem )
    : m_viewItem( viewItem )
  {}

  BaseViewItem *getViewItem() const
  {
    return m_viewItem;
  }

private:

  BaseViewItem *m_viewItem;
};