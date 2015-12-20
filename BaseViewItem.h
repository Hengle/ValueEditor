#pragma once

#include "DllExport.h"
#include <QtCore/QObject.h>
#include <QtCore/QVariant.h>
#include <QtGui/QTreeWidget.h>
#include <vector>

class BaseModelItem;
class BaseViewItem;

class VALUEEDIT_API ViewItemChildRouter : public QObject
{
  Q_OBJECT

  BaseViewItem *m_viewItem;
  int m_index;

public:

  ViewItemChildRouter(
    BaseViewItem *viewItem,
    int index
    );

  void connectToChild( BaseViewItem *childViewItem );

  void emitModelValueChanged( QVariant const &value );

signals:

  void modelValueChanged( QVariant const &value );

public slots:

  void onViewValueChanged( QVariant const &value, bool commit );
};

// The base item for the view-side of the equation.
// A BaseViewItem essentially represents a row in the
// treeview.  The base class handles communicating with
// the core, and should be implemented to handle specific
// UI duties (ie, showing widgets, etc).  

class VALUEEDIT_API BaseViewItem : public QObject
{
  // Friend the Factory to allow it to set our modelItem
  friend class ViewItemFactory;

  Q_OBJECT

  Q_DISABLE_COPY(BaseViewItem);
  
  // Every ViewItem has a name, which can be displayed 
  // in the TreeView, and may also be used to identify
  // this ViewItem.
  QString m_name;

  // A ViewItem may or may not have a ModelItem
  BaseModelItem *m_modelItem;

private:

  // This value is only setable by ViewitemFactory
  void setBaseModelItem( BaseModelItem* item )
    { m_modelItem = item; }

protected:

  typedef ViewItemChildRouter ChildRouter;

  ChildRouter *createChildRouter( int index )
    { return new ChildRouter( this, index ); }

public:

  BaseViewItem( QString const &name );
  ~BaseViewItem();

  // Returns a matching ModelItem for this ViewItem
  // May be null.
  BaseModelItem* GetModelItem()
    { return m_modelItem; }

  // Implement this function to build the widgets to
  // display the value represented by your class
  virtual QWidget *getWidget() = 0;

  // Get the name of this ViewItem
  QString const &getName() const
    { return m_name; }

  // Indicate if this ViewItem will return any 
  // ViewItems in the appendChildViewItems function
  virtual bool hasChildren() const;
  
  // Implement this function to add additional ViewItem
  // as children.  Default implementation adds ViewItems
  // for each child of the model item (if present)
  virtual void appendChildViewItems( QList<BaseViewItem *>& items) const;

  // Add the viewItems widgets to the tree item.  The default
  // implementation simply calls GetWidget and adds this
  // to the tree, however a ViewItem can override this function 
  // if more control is desired.
  virtual void setWidgetsOnTreeItem(
    QTreeWidget* treeWidget,
    QTreeWidgetItem * treeWidgetItem );

public slots:

  // Implement this slot to update the UI to the
  // passed variant.  If necessary, pass the update
  // down to this items children as well.
  virtual void onModelValueChanged( QVariant const &value ) = 0;

  // Implement this slot if we need to react when a child changes
  virtual void onChildViewValueChanged(
    int index,
    QVariant const &value,
    bool commit
    );
  
signals:

  // When this items widgets change, it should emit this signal
  void viewValueChanged(
    QVariant const &value,
    bool commit
    );
};

