#pragma once

#ifdef __AFX_H__ //使用mfc时才包含
#include "WndPublic.h"
#endif


// #if (_MSC_VER == 1600)	//vs2010
// 
// #if defined(_AFXDLL) || defined(_DLL)
// 	#if defined(_UNICODE) 
// 		#if defined(_DEBUG)
// 			#pragma comment(lib, "libwndcommon10mdud.lib")
// 		#else
// 			#pragma comment(lib, "libwndcommon10mdu.lib")
// 		#endif //_DEBUG
// 
// 	#else
// 		#if defined(_DEBUG)
// 			#pragma comment(lib, "libwndcommon10mdd.lib")
// 		#else
// 			#pragma comment(lib, "libwndcommon10md.lib")
// 		#endif //_DEBUG
// 	#endif //_UNICODE
// #else
// 	#if defined(_UNICODE) 
// 		#if defined(_DEBUG)
// 			#pragma comment(lib, "libwndcommonud.lib")
// 		#else
// 			#pragma comment(lib, "libwndcommonu.lib")
// 		#endif //_DEBUG
// 
// 	#else
// 		#if defined(_DEBUG)
// 			#pragma comment(lib, "libwndcommon10d.lib")
// 		#else
// 			#pragma comment(lib, "libwndcommon10.lib")
// 		#endif //_DEBUG
// 	#endif //_UNICODE
// #endif //_AFXDLL
// 
// #endif //(_MSC_VER == 1600)
// 
// #if (_MSC_VER == 1200)	//vc6
// 	#if defined(_UNICODE) 
// 		#error "libwndcommon not support!"
// 		//#if defined(_DEBUG)
// 		//	//#pragma comment(lib, "libcommonud.lib")
// 		//#else
// 		//	//#pragma comment(lib, "libcommonu.lib")
// 		//#endif //_DEBUG
// 
// 	#else
// 		#if defined(_DEBUG)
// 			#pragma comment(lib, "libwndcommond.lib")
// 		#else
// 			#pragma comment(lib, "libwndcommon.lib")
// 		#endif //_DEBUG
// 	#endif //_UNICODE
// #endif //(_MSC_VER == 1200)



#ifndef _LIBALL_NOAUTOLINK
	#ifndef _LIBWNDCOMMON_NOAUTOLINK
		//libwndcommon-vc100-x86-MD-Release-U
		#pragma warning(disable:4083)
		#pragma comment(lib, "libwndcommon-"  _LIB_VISUALSTUDIO_VERSION _LIB_PLATFORM _LIB_CONFIGURATION ".lib")
	#endif
#endif