#include "ColorViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QLabel.h>

ColorViewItem::ColorViewItem(
  const QVariant& value,
  const QString& name
  )
  : BaseViewItem( name )
  , m_label( new QLabel )
{
  QObject *labelObject = m_label;
  labelObject->setParent( this );
}

ColorViewItem::~ColorViewItem()
{
}

QWidget *ColorViewItem::getWidget()
{
  return m_label;
}

void ColorViewItem::UpdateViewValue( QVariant value )
{
  if ( value.canConvert( QVariant::String ) )
  {
    QString string = value.toString();
    m_label->setText( string );
  }
}

void ColorViewItem::onChildViewChanged( QVariant const &, QString const &, bool )
{
}

//////////////////////////////////////////////////////////////////////////
//

static ColorViewItem* CreateItem(
  BaseModelItem *modelItem,
  QString const &name,
  QVariant const &value,
  char const *tag
  )
{
  return nullptr;
}
EXPOSE_VIEW_ITEM( ColorViewItem, CreateItem, 3 );
