#pragma once

#include <QtCore/qglobal.h>

#if defined(VALUEEDITOR_BUILD)
#  define VALUEEDIT_API Q_DECL_EXPORT
#else
#  define VALUEEDIT_API Q_DECL_IMPORT
#endif