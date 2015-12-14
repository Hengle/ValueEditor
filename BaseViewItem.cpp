#include "BaseViewItem.h"
#include "BaseModelItem.h"


BaseViewItem::BaseViewItem( QString const &name )
  : m_name( name )
{
}


BaseViewItem::~BaseViewItem()
{
}

size_t BaseViewItem::NumChildren()
{
  return m_children.size();
}

BaseViewItem* BaseViewItem::GetChild( size_t i )
{
  return m_children[i];
}

void BaseViewItem::AddChild( BaseViewItem* pChild, bool doConnect/*=false*/ )
{
  m_children.push_back(pChild);

  if (doConnect)
  {
    connect(
      pChild, SIGNAL( ViewValueChanged( QVariant, QString, bool ) ),
      this, SLOT( onChildViewChanged( QVariant const &, QString const &, bool ) )
      );

  }
}

const QString& BaseViewItem::GetName()
{
  return m_name;
}

void BaseViewItem::onChildViewChanged(
  QVariant const &,
  QString const &,
  bool
  )
{
  /* default is no-op */
}
