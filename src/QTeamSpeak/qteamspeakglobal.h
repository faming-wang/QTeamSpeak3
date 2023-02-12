#pragma once

#include <QtCore/qobject.h>

#ifndef QT_STATIC
#  if defined(QT_BUILD_WIDGETS_LIB)
#    define Q_WIDGETS_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WIDGETS_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_WIDGETS_EXPORT
#endif
