#pragma once

#include "BaseViewItem.h"
#include <QtGui/QLabel.h>

class ColorViewItem : public BaseViewItem
{
private:
  
  QLabel *m_label;

public:

  ColorViewItem( const QVariant& value, const QString& name );
  ~ColorViewItem();

  virtual QWidget *getWidget() /*override*/;

  void UpdateViewValue( QVariant value ) /*override*/;

  virtual void onChildViewChanged(
    QVariant const &,
    QString const &,
    bool
    ) /*override*/;
};
