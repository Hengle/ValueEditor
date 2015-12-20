#pragma once
#pragma once

#include "DllExport.h"
#include <QtCore/QObject.h>
#include <QtCore/QVariant.h>

// The base model item is the base class for defining
// items on the model.  This provides a common
// interface for supplying data from the FabricCore, and
// connecting notifications.  The view consumes a 
// tree/list? of BaseModelItems to build it's UI
class VALUEEDIT_API BaseModelItem : public QObject
{
	Q_OBJECT

	Q_DISABLE_COPY(BaseModelItem);

public:

	BaseModelItem();
	virtual ~BaseModelItem();

	// The model is a tree
	virtual size_t NumChildren() = 0;
	virtual BaseModelItem* GetChild(size_t i) = 0;

	// The name of this nodes data
	virtual QString GetName() = 0;
	// The type of data exposed.  This should
	// function should be redundant though, we
	// should simply use the type of the QVariant
	// returned from GetValue
	//virtual QString GetType() = 0;

	// We need to define a metadata syntax for 
	// additional type-info.  For example, it should
	// be possible using metadata to request a value
	// be displayed in a certain way, eg as an angle
	// or as a percentage, or 
	virtual QString GetMetadata(QString string);

	// Return a copy of this classes value
	virtual QVariant GetValue() = 0;

public slots:

	// The BaseModelItem is responsible for receiving values back from 
	// the the UI and setting them on the core object.
	// It is guaranteed that the QVariant value here will be equivalent
	// to the QVariant returned from GetValue
	virtual void onViewValueChanged(
		QVariant const& /*value*/,
		bool /*commit*/
		)
		{}

signals:

	// Connect to this signal to be notified
	// when the core value changes.
	void modelValueChanged( QVariant const &newValue );
};

