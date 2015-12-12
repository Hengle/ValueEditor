#pragma once

#include <vector>

class BaseViewItem;

// This factory is responsible for returning the appropriate BaseViewItem
// when creating for a given data type
class ViewItemFactory
{
private:
	// Friend ViewItemCreator to allow it to 
	// register itself with us
	friend class BaseViewItemCreator;

	std::vector<BaseViewItemCreator*> m_creators;

	//////////////////////////////////////////////////////////////////////////
	ViewItemFactory();
	~ViewItemFactory();

	// Register arbitrary widget creators 
	// Note - It is not necessary to explicitly register 
	// any ValueCreator, as soon as an instance of the
	// the class is created it will automatically
	// register itself with the system
	bool RegisterCreator(BaseViewItemCreator* creator);
	// DeRegister widget creators.  This is called
	// automatically when an item is released.
	void DeRegisterCreator(BaseViewItemCreator* creator);

public:

	static ViewItemFactory* GetInstance();
	//////////////////////////////////////////////////////////////////////////
	


	// Create the most appropriate value editor given the following data
	// \data The data being edited.  We create a BaseViewItem that matches the
	//	type of this data.
	// \viewtype[optional] What dimension the data represents.  For example, a 
	//		float can represent any of an angle/ratio/distance etc.
	// \tag[optional] One more piece of metadata, just in case you want to 
	//		only display a value for a tagged value.
	// TODO: Perhaps just pass in a MetaData option here to represent all metadata?
	BaseViewItem* CreateViewItem(const QVariant& data, const char* viewtype, const char* tag = nullptr);
};