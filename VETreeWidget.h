#pragma once

#include <QtGui/QTreeWidget.h>

class BaseViewItem;

class VALUEEDIT_API VETreeWidget : public QTreeWidget
{
  Q_OBJECT

public:

  VETreeWidget( BaseViewItem *rootViewItem );

protected slots:

  void onTreeWidgetItemExpanded( QTreeWidgetItem *_treeWidgetItem );

  void onTreeWidgetItemCollapsed( QTreeWidgetItem *_treeWidgetItem );
};
