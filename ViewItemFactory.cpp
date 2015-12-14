#include "ViewItemFactory.h"
#include "BaseViewItemCreator.h"
#include "BaseModelItem.h"
#include "BaseViewItem.h"

ViewItemFactory::ViewItemFactory()
{

}

ViewItemFactory::~ViewItemFactory()
{
  // destruct all remaining creators.
  while (!m_creators.empty())
    (*m_creators.rbegin())->DeleteThis();
}

ViewItemFactory* ViewItemFactory::GetInstance()
{
  static ViewItemFactory instance;
  return &instance;
}


BaseViewItem* ViewItemFactory::BuildView(BaseModelItem* model)
{
  if (model == nullptr)
    return nullptr;

  BaseViewItem* viewItem = CreateViewItem(model->GetValue(), model->GetName());

  if (viewItem != nullptr)
  {
    for (int i = 0; i < model->NumChildren(); i++)
    {
      BaseViewItem* childView = BuildView(model->GetChild(i));
      viewItem->AddChild(childView);
    }
    viewItem->SetBaseModelItem( model );
  }

  return viewItem;
}

// sort using a custom function object
struct CreatorSort
{
  bool operator()( BaseViewItemCreator* a, BaseViewItemCreator* b )
  {
    return a->Priority() < b->Priority();
  }
};

bool ViewItemFactory::RegisterCreator(BaseViewItemCreator* creator)
{
  for ( CreatorIT itr = creatorBegin(); itr != creatorEnd(); itr++ )
  {
    if (*itr == creator)
      return false;
  }
  m_creators.push_back(creator);
  // Sort creators in order of priority
  std::sort( m_creators.begin(), m_creators.end(), CreatorSort() );
  return true;
}

void ViewItemFactory::DeRegisterCreator(BaseViewItemCreator* creator)
{
  for ( CreatorIT itr = creatorBegin(); itr != creatorEnd(); itr++ )
  {
    if (*itr == creator)
    {
      m_creators.erase(itr);
      break;
    }
  }
}

BaseViewItem* ViewItemFactory::CreateViewItem(const QVariant& data, const QString& name, const char* tag)
{
  // iterate in reverse.  This ensures we test the most-specialized types
  // before testing the more generalized types
  for ( CreatorRIT itr = creatorRBegin(); itr != creatorREnd(); itr++ )
  {
    BaseViewItem* viewItem = (*itr)->CreateItem(data, name, tag);
    if (viewItem != nullptr)
      return viewItem;
  }

  return nullptr;
}

