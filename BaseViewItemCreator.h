#pragma once

#include <QtCore\QVariant>

class BaseViewItem;

// A ViewItemCreator allows plugging in custom ViewItem implementations.
// An instance of this class should be registered with the ViewItemFactor.
// Whenever the system needs to create a ViewItem for a piece of data,
// the Factory will query each ViewItemCreator in order until a Creator
// matches the input parameters.
class BaseViewItemCreator
{
public:

	// This class will automatically register itself with the 
	// ViewItemFactory on creation.
	BaseViewItemCreator();
	// This class will automatically remove itself from the 
	// ViewItemFactory on release.
	~BaseViewItemCreator();

	// Implement this function to return true if this 
	// creator can generate a viewitem for the input data.
	virtual bool Matches(QVariant data, const char* type, const char* tag) = 0;

	// Create the view item.
	// NOTE - We may remove the Matches function and just rely
	// on this function returning nullptr if it doesn't match.
	virtual BaseViewItem* CreateItem(const QVariant& data, const char* type, const char* tag) = 0;

	// Implement this function to delete this class, it will 
	// be called when the item is released.
	virtual void DeleteThis() = 0;
};