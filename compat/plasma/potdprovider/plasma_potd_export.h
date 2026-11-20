// SPDX-License-Identifier: GPL-2.0-or-later
//
// Vendored equivalent of the plasma_potd_export.h header that KDE's
// ecm_generate_export_header() produces when kdeplasma-addons is built
// (BASE_NAME PLASMA_POTD). It is normally installed alongside
// potdprovider.h by the Plasma Workspace "Devel" package, but that
// package isn't available on every distro (e.g. Kubuntu/Debian). See
// the top-level CMakeLists.txt and README.md for details.

#ifndef PLASMA_POTD_EXPORT_H
#define PLASMA_POTD_EXPORT_H

#ifdef PLASMA_POTD_STATIC_DEFINE
#  define PLASMA_POTD_EXPORT
#  define PLASMA_POTD_NO_EXPORT
#else
#  ifndef PLASMA_POTD_EXPORT
#    ifdef plasmapotdprovidercore_EXPORTS
        /* We are building this library */
#      define PLASMA_POTD_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define PLASMA_POTD_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef PLASMA_POTD_NO_EXPORT
#    define PLASMA_POTD_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef PLASMA_POTD_DECL_DEPRECATED
#  define PLASMA_POTD_DECL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef PLASMA_POTD_DECL_DEPRECATED_EXPORT
#  define PLASMA_POTD_DECL_DEPRECATED_EXPORT PLASMA_POTD_EXPORT PLASMA_POTD_DECL_DEPRECATED
#endif

#ifndef PLASMA_POTD_DECL_DEPRECATED_NO_EXPORT
#  define PLASMA_POTD_DECL_DEPRECATED_NO_EXPORT PLASMA_POTD_NO_EXPORT PLASMA_POTD_DECL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PLASMA_POTD_NO_DEPRECATED
#    define PLASMA_POTD_NO_DEPRECATED
#  endif
#endif

#define PLASMA_POTD_DECL_DEPRECATED_TEXT(text) PLASMA_POTD_DECL_DEPRECATED

#if defined(PLASMA_POTD_NO_DEPRECATED)
#  undef PLASMA_POTD_DEPRECATED
#  define PLASMA_POTD_DEPRECATED_EXPORT PLASMA_POTD_EXPORT
#  define PLASMA_POTD_DEPRECATED_NO_EXPORT PLASMA_POTD_NO_EXPORT
#elif defined(PLASMA_POTD_NO_DEPRECATED_WARNINGS)
#  define PLASMA_POTD_DEPRECATED
#  define PLASMA_POTD_DEPRECATED_EXPORT PLASMA_POTD_EXPORT
#  define PLASMA_POTD_DEPRECATED_NO_EXPORT PLASMA_POTD_NO_EXPORT
#else
#  define PLASMA_POTD_DEPRECATED PLASMA_POTD_DECL_DEPRECATED
#  define PLASMA_POTD_DEPRECATED_EXPORT PLASMA_POTD_DECL_DEPRECATED_EXPORT
#  define PLASMA_POTD_DEPRECATED_NO_EXPORT PLASMA_POTD_DECL_DEPRECATED_NO_EXPORT
#endif

/* No deprecated API had been removed from build */
#define PLASMA_POTD_EXCLUDE_DEPRECATED_BEFORE_AND_AT 0

#define PLASMA_POTD_BUILD_DEPRECATED_SINCE(major, minor) 1

#ifdef PLASMA_POTD_NO_DEPRECATED
#  define PLASMA_POTD_DISABLE_DEPRECATED_BEFORE_AND_AT 0x20000
#endif
#ifdef PLASMA_POTD_NO_DEPRECATED_WARNINGS
#  define PLASMA_POTD_DEPRECATED_WARNINGS_SINCE 0
#endif

#ifndef PLASMA_POTD_DEPRECATED_WARNINGS_SINCE
#  ifdef PLASMA_POTD_DISABLE_DEPRECATED_BEFORE_AND_AT
#    define PLASMA_POTD_DEPRECATED_WARNINGS_SINCE PLASMA_POTD_DISABLE_DEPRECATED_BEFORE_AND_AT
#  else
#    define PLASMA_POTD_DEPRECATED_WARNINGS_SINCE 0x20000
#  endif
#endif

#ifndef PLASMA_POTD_DISABLE_DEPRECATED_BEFORE_AND_AT
#  define PLASMA_POTD_DISABLE_DEPRECATED_BEFORE_AND_AT 0
#endif

#ifdef PLASMA_POTD_DEPRECATED
#  define PLASMA_POTD_ENABLE_DEPRECATED_SINCE(major, minor) (((major<<16)|(minor<<8)) > PLASMA_POTD_DISABLE_DEPRECATED_BEFORE_AND_AT)
#else
#  define PLASMA_POTD_ENABLE_DEPRECATED_SINCE(major, minor) 0
#endif

#endif /* PLASMA_POTD_EXPORT_H */
