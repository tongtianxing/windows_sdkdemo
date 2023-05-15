#pragma once


#include "safedef.h"
#include "Bit.h"



#include "StaticObject.h"
#include "ObjPool.h"
#include "ObjPoolEx.h"


#include "MutexLock.h"
#include "md5.h"

#include "logtrace.h"

#include <ObjTemplate.h>




// _MSC_VER ==> https://learn.microsoft.com/zh-cn/cpp/preprocessor/predefined-macros?view=msvc-170&viewFallbackFrom=vs-2019
#if _MSC_VER == 1600
#define _LIB_VISUALSTUDIO_VERSION "vc100"
#endif
#if _MSC_VER == 1700	//vs2012
#define _LIB_VISUALSTUDIO_VERSION "vc110"
#endif
#if _MSC_VER == 1800	//vs2013
#define _LIB_VISUALSTUDIO_VERSION "vc120"
#endif
#if _MSC_VER == 1900	//vs2015
#define _LIB_VISUALSTUDIO_VERSION "vc140"
#endif
#if (_MSC_VER >= 1910 && _MSC_VER <= 1916)	//vs2017
#define _LIB_VISUALSTUDIO_VERSION "vc141"
#endif
#if (_MSC_VER >= 1920 && _MSC_VER <= 1929)	//vs2019
#define _LIB_VISUALSTUDIO_VERSION "vc142"
#endif
#if (_MSC_VER >= 1930)	//vs2022
#define _LIB_VISUALSTUDIO_VERSION "vc143"
#endif

#ifndef _LIB_VISUALSTUDIO_VERSION
#error "Unknown Visual Studio version"
#endif


//#defined ENABLE_RELEASE_DEBUG

#if !defined(_AFXDLL) && !defined(_DLL)
	#define _LIB_CONFIGURATION1 "-MT"
#else
	#define _LIB_CONFIGURATION1 "-MD"
#endif


#if defined(_DEBUG)
	#define _LIB_CONFIGURATION2 "-Debug"
#else
	#define _LIB_CONFIGURATION2 "-Release"
#endif


#if defined(_UNICODE)
	#define _LIB_CONFIGURATION3 "-U"
#else
	#define _LIB_CONFIGURATION3 ""
#endif

#if !defined(_DEBUG) && defined(ENABLE_RELEASE_DEBUG)
	#define _LIB_CONFIGURATION4 "-D"
#else
	#define _LIB_CONFIGURATION4 ""
#endif

#define _LIB_CONFIGURATION	_LIB_CONFIGURATION1 _LIB_CONFIGURATION2 _LIB_CONFIGURATION3 _LIB_CONFIGURATION4

#if defined(_WIN64)
	#define _LIB_PLATFORM "-x64"
#else
	#define _LIB_PLATFORM "-x86"
#endif

#if defined(ENABLE_RELEASE_DEBUG)
#else
#endif

#ifndef _LIBALL_NOAUTOLINK

//libopensource-vc100-x86-MD-Release-U
#ifndef _OPENSOURCELIB_NOAUTOLINK
	#pragma comment(lib, "libopensource-"  _LIB_VISUALSTUDIO_VERSION _LIB_PLATFORM _LIB_CONFIGURATION ".lib")
	//#pragma message("Automatically linking with libopensource"  _LIB_VISUALSTUDIO_VERSION _LIB_PLATFORM _LIB_CONFIGURATION "." _XTPLIB_LINK_TYPE)
#endif

#ifndef _LIBCOMMON_NOAUTOLINK
//libcommon-vc100-x86-MD-Release-U
#pragma comment(lib, "libcommon-"  _LIB_VISUALSTUDIO_VERSION _LIB_PLATFORM _LIB_CONFIGURATION ".lib")
#endif


//LOG_USE_STATIC_LINK  使用静态库libcommon中的日志类(一般仅用来编译到旧版本时使用)
//_LOG_NO_AUTOLINK  日志库不自动链接,liblogfile库才使用
#if !defined(LOG_USE_STATIC_LINK) && !defined(_LIBCOMMON_NOAUTOLINK) && !defined(_LOG_NO_AUTOLINK)
#pragma comment(lib, "liblogfile.lib")
#endif


#endif
