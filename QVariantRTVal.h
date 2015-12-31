#pragma once

#include <FabricCore.h>
#include <QtCore/QVariant>

// Import RTVal into the QVariant types
Q_DECLARE_METATYPE(FabricCore::RTVal);

class RTVariant : public QVariant
{
public:
  static void injectRTHandler();

private:
  // Overrides for built-in functionality

  // isNull tests rtVal for isValid
  static bool rtIsNull( const QVariant::Private *d);

  static bool rtCanConvert( const QVariant::Private *d, Type t );

  static bool rtConvert( const QVariant::Private *d, QVariant::Type t, void *result, bool *ok );

  static void rtStreamDebug( QDebug dbg, const QVariant &v );

  static const Handler* origh;

  static const void *constData( const QVariant::Private *d );

  static const FabricCore::RTVal& value( const Private *p ) {
    // Code taken from QVariant::value<T>
    return *reinterpret_cast<const FabricCore::RTVal*>(p->is_shared ? p->data.shared->ptr : &p->data.ptr);
  }

};

inline bool isRTVal( const QVariant& var ) {
  if (var.type() != QVariant::UserType)
    return false;
  if (var.userType() != qMetaTypeId<FabricCore::RTVal>())
    return false;
  return true;
}

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

inline bool isDouble( const FabricCore::RTVal& val )
{
  if (val.isValid())
  {
    const char* typeName = val.getTypeNameCStr();
    if (strcmp( typeName, "Float32" ) == 0)
      return true;
    else if (strcmp( typeName, "Float64" ) == 0)
      return true;
    else if (strcmp( typeName, "Scalar" ) == 0)
      return true;
  }
  return false;
}

inline bool isDouble( const QVariant& var )
{
  if (var.type() == QVariant::Double
       || var.type() == QMetaType::Float)
    return true;

  FabricCore::RTVal val = toRTVal( var );
  return isDouble( val );
}

inline double getDouble( const FabricCore::RTVal& val )
{
  const char* typeName = val.getTypeNameCStr();
  if (strcmp( typeName, "Float64" ) == 0)
    return val.getFloat64();
  else
    return val.getFloat32();
}

inline double getDouble( const QVariant& var )
{
  bool ok = false;
  double res = var.toDouble( &ok );
  if (!ok)
  {
    FabricCore::RTVal val = toRTVal( var );
    res = getDouble( val );
  }
  return res;
}

inline bool VariantToRTVal(const QVariant& var, FabricCore::RTVal& val)
{
	if (var.userType() == qMetaTypeId<FabricCore::RTVal>())
	{
		val = var.value<FabricCore::RTVal>();
		return true;
	}

	FabricCore::Context ctxt;
	// Convert into the type of the RTVal
	const char* ctype = val.getTypeNameCStr();
	if (strcmp(ctype, "Float32") == 0)
		val.setFloat32(var.toFloat());
  else if (strcmp( ctype, "Scalar" ) == 0)
    val.setFloat32( var.toFloat() );
  else if (strcmp(ctype, "Float64") == 0)
		val = FabricCore::RTVal::ConstructFloat64(ctxt, var.toFloat());
	else if (strcmp(ctype, "String") == 0)
	{
		QByteArray asciiArr = var.toString().toAscii();
		val = FabricCore::RTVal::ConstructString(ctxt, asciiArr.data());
	}
	else // Unknown type?
	{
		//assert(!"Unknown type in VariantToRTVal");
		return false;
	}
	return true; // Assume successful

}
