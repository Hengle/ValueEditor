#pragma once

#pragma warning(push, 0)
#include <FabricCore.h>
#pragma pop
#include <QtCore/qvariant.h>
#include <assert.h>

// Import RTVal into the QVariant types
Q_DECLARE_METATYPE(FabricCore::RTVal);


// Initially at least - A set of functions for 
// converting RTVal <--> QVariant
inline QVariant toVariant(const FabricCore::RTVal& val) 
{ 
	return QVariant::fromValue<FabricCore::RTVal>(val); 
}

inline FabricCore::RTVal toRTVal(const QVariant var) 
{
	if (var.userType() == qMetaTypeId<FabricCore::RTVal>())
		return var.value<FabricCore::RTVal>();

	return FabricCore::RTVal();
}

inline bool VariantToRTVal(FabricCore::Client& client, const QVariant& var, FabricCore::RTVal& val)
{
	if (var.userType() == qMetaTypeId<FabricCore::RTVal>())
	{
		val = var.value<FabricCore::RTVal>();
		return true;
	}

	FabricCore::Context ctxt;
	// Convert into the type of the RTVal
	const char* ctype = val.getTypeNameCStr();
	if (ctype == "Float32")
		val.setFloat32(var.toFloat());
	else if (ctype == "Float64")
		val = FabricCore::RTVal::ConstructFloat64(ctxt, var.toFloat());
	else if (ctype == "String")
	{
		QByteArray asciiArr = var.toString().toAscii();
		val = FabricCore::RTVal::ConstructString(ctxt, asciiArr.data());
	}
	else // Unknown type?
	{
		assert(!"Unknown type in VariantToRTVal");
		return false;
	}
	return true; // Assume successful

}