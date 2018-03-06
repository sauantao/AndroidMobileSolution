/*
    Copyright (C) 2014  Intel Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef XFSTKDLDRAPI_GLOBAL_H
#define XFSTKDLDRAPI_GLOBAL_H

#if defined XFSTK_OS_WIN
#else
#include <QtCore/qglobal.h>
#endif

#if defined XFSTK_OS_WIN

#if defined(XFSTKDLDRAPI_LIBRARY)
#  define XFSTKDLDRAPISHARED_EXPORT __declspec(dllexport)
#else
#  define XFSTKDLDRAPISHARED_EXPORT __declspec(dllimport)
#endif

#else

#if defined(XFSTKDLDRAPI_LIBRARY)
#  define XFSTKDLDRAPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define XFSTKDLDRAPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif

#endif // XFSTKDLDRAPI_GLOBAL_H
