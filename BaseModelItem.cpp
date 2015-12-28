#include "stdafx.h"
#include "BaseModelItem.h"

BaseModelItem::BaseModelItem()
{
}


BaseModelItem::~BaseModelItem()
{
}

FTL::JSONObject* BaseModelItem::GetMetadata()
{
  return NULL;
}

// Include MOC'ed file here, in order
// to support PCH on windows.
#include "moc_BaseModelItem.cpp"