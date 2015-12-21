#pragma once
#include "BaseViewItem.h"

class QPushButton;

class ColorViewItem : public BaseViewItem
{
private:

  Q_OBJECT

  QPushButton* m_button;

public:

  ColorViewItem( const QVariant& value, const QString& name );
  ~ColorViewItem();

  virtual QWidget *getWidget() /*override*/;

  virtual void onModelValueChanged( QVariant const &value ) /*override*/;

  void setButtonColor( const QColor & color );

public slots:

  // Slot triggered when pushing background button
  void pickColor();
  void onColorChanged( QColor color );
  void onColorSelected( QColor color );
};
