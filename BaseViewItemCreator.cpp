#include "BaseViewItemCreator.h"
#include "ViewItemFactory.h"

BaseViewItemCreator::BaseViewItemCreator()
{
	ViewItemFactory* factory = ViewItemFactory::GetInstance();
	if (factory != nullptr)
		factory->RegisterCreator(this);
}

BaseViewItemCreator::~BaseViewItemCreator()
{
	ViewItemFactory* factory = ViewItemFactory::GetInstance();
	if (factory != nullptr) 
		factory->DeRegisterCreator(this);
}