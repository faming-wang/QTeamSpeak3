#pragma once

#include <QtCore/qglobal.h>

#define BUILD_STATIC

#ifndef BUILD_STATIC
# if defined(TEAMSPEAKSDK_LIB)
#  define Q_DECL_EXPORT
# else
#  define Q_DECL_IMPORT
# endif
#else
# define TEAMSPEAKSDK_EXPORT
#endif

