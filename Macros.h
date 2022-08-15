#pragma once

//平台和编译器相关的宏定义

#ifdef _MSC_VER
#define VSExport __declspec(dllexport)
#define VSImport __declspec(dllimport)
#define VSCall _cdecl
#endif

#ifdef __clang__
#define VSExport __attribute__((visibility("default")))
#define VSImport __attribute__((visibility("default")))
#define VSCall __attribute__((cdecl))
#endif

#ifdef __GNUC__
#define VSExport __attribute__((visibility("default")))
#define VSImport __attribute__((visibility("default")))
#define VSCall __attribute__((cdecl))
#endif

#if ! (defined (_MSC_VER) || defined (__clang__) || defined (__GNUC__))
#define VSExport 
#define VSImport 
#define VSCall _cdecl
#endif

#if VS_BUILD_DLL
#define VSAPI VSExport
#else
#define VSAPI VSImport
#endif // VS_BUILD_DLL