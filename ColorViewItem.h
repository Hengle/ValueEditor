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

  virtual void onModelValueChanged( QVariant const &value ) /*override*/;

  virtual void onChildViewValueChanged(
    QVariant const &,
    QString const &,
    bool
    ) /*override*/;
};
