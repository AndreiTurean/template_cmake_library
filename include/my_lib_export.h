#pragma once
/*
* The example bellow was extracted from https://gcc.gnu.org/wiki/Visibility
*/

#// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
#define MY_LIB_IMPORT __declspec(dllimport)
#define MY_LIB_EXPORT __declspec(dllexport)
#define MY_LIB_LOCAL
#else
#if __GNUC__ >= 4
#define MY_LIB_IMPORT __attribute__ ((visibility ("default")))
#define MY_LIB_EXPORT __attribute__ ((visibility ("default")))
#define MY_LIB_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define MY_LIB_IMPORT
#define MY_LIB_EXPORT
#define MY_LIB_LOCAL
#endif
#endif

// Now we use the generic helper definitions above to define LIBRARY_API and LIBRARY_LOCAL.
// LIBRARY_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// LIBRARY_LOCAL is used for non-api symbols.

#ifdef LIBRARY_DLL // defined if LIBRARY is compiled as a DLL
#ifdef MY_LIB_EXPORT // defined if we are building the LIBRARY DLL (instead of using it)
#define LIBRARY_API MY_LIB_EXPORT
#else
#define LIBRARY_API MY_LIB_IMPORT
#endif
#define LIBRARY_LOCAL MY_LIB_LOCAL
#else // LIBRARY_DLL is not defined: this means LIBRARY is a static lib.
#define LIBRARY_API
#define LIBRARY_LOCAL
#endif