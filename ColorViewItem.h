#pragma once

#include "BaseViewItem.h"

class ColorViewItem : public BaseViewItem
{
private:
  // WE cache the value, and print it out.  This is so if this class is
  // used for something it should not be, it will at least be printed
  // out (and we can see what type it should be).
  QVariant m_value;

public:

  ColorViewItem( const QVariant& value, const QString& name );
  ~ColorViewItem();

  QWidget* BuildWidgets( bool expanded ) /*override*/;

  QVariant GetValue() /*override*/;

  void UpdateViewValue( QVariant value ) /*override*/;

  virtual void onChildViewChanged(
    QVariant const &,
    QString const &,
    bool
    ) /*override*/;
};
