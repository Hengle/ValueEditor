#include "ColorViewItem.h"
#include "BaseViewItemCreator.h"
#include <QtGui/QLabel.h>
#include <assert.h>

ColorViewItem::ColorViewItem(
  const QVariant& value,
  const QString& name
  )
  : BaseViewItem( name )
  , m_label( 0 )
{
}

ColorViewItem::~ColorViewItem()
{
}

QWidget *ColorViewItem::getWidget()
{
  assert( !m_label );
  m_label = new QLabel;
  return m_label;
}

void ColorViewItem::onModelValueChanged( QVariant const &value )
{
  if ( value.canConvert( QVariant::String ) )
  {
    QString string = value.toString();
    assert( m_label );
    m_label->setText( string );
  }
}

void ColorViewItem::onChildViewValueChanged( QVariant const &, QString const &, bool )
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
