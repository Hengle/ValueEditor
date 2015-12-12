#pragma once

#include <vector>

class BaseModelItem;

// The base item for the view-side of the equation.
// A BaseViewItem essentially represents a row in the
// treeview.  The base class handles communicating with
// the core, and should be implemented to handle specific
// UI duties (ie, showing widgets, etc).  

class BaseViewItem :
  public QObject
{
  Q_OBJECT

  Q_DISABLE_COPY(BaseViewItem);

  QString m_name;

  // A viewitem may be directly connected
  // to a BaseModelItem
  BaseModelItem* m_modelitem;

protected:

  std::vector<BaseViewItem*> m_children;

public:
  BaseViewItem( QString name );
  ~BaseViewItem();

  size_t NumChildren();
  BaseViewItem* GetChild( size_t i );

  // A a child to this item. If connect is true, then we will also
  // wire up the childs ViewValueChanged to this classes OnChildChanged
  void AddChild( BaseViewItem* pItem, bool doConnect = false );

  // Connect this ViewItem to the passed BaseModelItem
  // This allows this ViewItem to directly query the 
  // BaseModelItem for its values, and will wire together
  // the bi-directional update signals.
  void SetBaseModelItem( BaseModelItem* pItem );

  // Implement this function to build the widgets to
  // display the value represented by your class
  virtual QWidget* BuildWidgets( bool expanded ) = 0;

  // Implement this function to return the current widget value
  virtual QVariant GetValue() = 0;

  // If connected to a ModelItem, returns that ModelItem's
  // value directly.  This is intended to be used to 
  // initialize widget values.
  QVariant GetModelValue();

  // Get the name of this ViewItem
  const QString& GetName();

  // If connected to a model, get's its values and
  // updates the widget values from it.
  void UpdateValueFromModel();

public slots:

  // Implement this slot to update the UI to the
  // passed variant.  If necessary, pass the update
  // down to this items children as well.
  virtual void UpdateViewValue( QVariant value ) = 0;

  // Implement this slot if we need to react when a child changes
  virtual void OnChildChanged( QVariant value, QString name, bool commit );
signals:

  // When this items widgets change, it should emit this signal
  void ViewValueChanged( QVariant value, QString name, bool commit );
};

