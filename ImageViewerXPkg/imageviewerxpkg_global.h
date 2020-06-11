#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMAGEVIEWERXPKG_LIB)
#  define IMAGEVIEWERXPKG_EXPORT Q_DECL_EXPORT
# else
#  define IMAGEVIEWERXPKG_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMAGEVIEWERXPKG_EXPORT
#endif
