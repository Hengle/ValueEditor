#include "BaseViewItem.h"
#include "BaseModelItem.h"


BaseViewItem::BaseViewItem( QString name )
  : m_name(name)
  , m_modelitem( 0 )
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
    connect( pChild, SIGNAL( ViewValueChanged( QVariant, QString, bool ) ),
         this, SLOT( OnChildChanged( QVariant, QString, bool ) ) );

  }
}

void BaseViewItem::SetBaseModelItem( BaseModelItem* pItem )
{
  m_modelitem = pItem;
  if (pItem != nullptr)
  {
    connect( this, SIGNAL( ViewValueChanged( QVariant, QString, bool ) ),
         pItem, SLOT( UpdateModelValue( QVariant, QString, bool ) ) );

    connect( pItem, SIGNAL( ModelValueChanged( QVariant ) ),
         this, SLOT( UpdateViewValue( QVariant ) ) );
  }
}

QVariant BaseViewItem::GetModelValue()
{
  if (m_modelitem != nullptr)
  {
    return m_modelitem->GetValue();
  }
  return QVariant();
}

const QString& BaseViewItem::GetName()
{
  return m_name;
}

void BaseViewItem::UpdateValueFromModel()
{
  if (m_modelitem != nullptr)
  {
    QVariant value = m_modelitem->GetValue();
    if ( value.type() != QVariant::Invalid )
    {
      UpdateViewValue(value);
    }
  }
}

void BaseViewItem::OnChildChanged(QVariant, QString, bool)
{
  /* default is no-op */
}
