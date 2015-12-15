#pragma once

#include <DllExport.h>
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
  Q_OBJECT

  Q_DISABLE_COPY(BaseViewItem);

  QString m_name;

protected:

  typedef ViewItemChildRouter ChildRouter;

  ChildRouter *createChildRouter( int index )
    { return new ChildRouter( this, index ); }

public:

  class TreeWidgetItem : public QTreeWidgetItem
  {
  public:

    TreeWidgetItem( BaseViewItem *viewItem )
      : m_viewItem( viewItem )
      {}

    BaseViewItem *getViewItem() const
      { return m_viewItem; }

  private:

    BaseViewItem *m_viewItem;
  };

  BaseViewItem( QString const &name );
  ~BaseViewItem();

  // Implement this function to build the widgets to
  // display the value represented by your class
  virtual QWidget *getWidget() = 0;

  // Get the name of this ViewItem
  QString const &getName() const
    { return m_name; }

  virtual bool hasChildren() const = 0;

  virtual QList<BaseViewItem *> createChildViewItems() const;

  void addToTreeWidget(
    QTreeWidget *treeWidget,
    TreeWidgetItem *parentTreeWidgetItem
    );

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

