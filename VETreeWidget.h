#pragma once

#include <QtGui/QTreeWidget.h>
#include "DllExport.h"

class BaseViewItem;
class BaseModelItem;

class VALUEEDIT_API VETreeWidget : public QTreeWidget
{
  Q_OBJECT

public:

  VETreeWidget( );

  void createTreeWidgetItem( BaseViewItem* viewItem, QTreeWidgetItem* parent );

public slots:

  void onSetModelItem( BaseModelItem* pItem );

protected slots:

  void onTreeWidgetItemExpanded( QTreeWidgetItem *_treeWidgetItem );

  void onTreeWidgetItemCollapsed( QTreeWidgetItem *_treeWidgetItem );
};
