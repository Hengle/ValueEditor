#pragma once

#include "DllExport.h"
#include <QtCore/QObject.h>
#include <QtCore/QVariant.h>
#include <QtGui/QTreeWidget.h>
#include <vector>

class BaseModelItem;
class BaseViewItem;

namespace FTL {
  class JSONObject;
}

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

public:

  BaseViewItem( QString const &name );
  virtual ~BaseViewItem();

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
  virtual void appendChildViewItems( QList<BaseViewItem *>& items);

  // Add the viewItems widgets to the tree item.  The default
  // implementation simply calls GetWidget and adds this
  // to the tree, however a ViewItem can override this function 
  // if more control is desired.
  virtual void setWidgetsOnTreeItem(
    QTreeWidget* treeWidget,
    QTreeWidgetItem * treeWidgetItem );

  // Implement this function if ViewItem uses metadata to
  // set its behaviour.  This function may be called at any
  // time if the metadata associated with this item changes.
  virtual void updateMetadata( FTL::JSONObject* /*metaData*/ ) {};

public slots:

  // Implement this slot to update the UI to the
  // passed variant.  If necessary, pass the update
  // down to this items children as well.
  virtual void onModelValueChanged( QVariant const &value ) = 0;
  
signals:

  // When this items widgets change, it should emit this signal
  void viewValueChanged(
    QVariant const &value,
    bool commit
    );
};

