#ifndef _TTX_TYPE_DEF_H_
#define _TTX_TYPE_DEF_H_

#define TTX_MAX_PATH 	260

//帧类型定义
#define TTX_FRM_TYPE_I			0		//I帧
#define TTX_FRM_TYPE_P			1		//P帧
#define TTX_FRM_TYPE_A			2		//音频帧
#define TTX_FRM_TYPE_INFO		3		//信息帧

#define TTX_RESOLUTION_QCIF				1	//分辨率
#define TTX_RESOLUTION_CIF				2	//分辨率
#define TTX_RESOLUTION_HD1				3	//分辨率
#define TTX_RESOLUTION_D1				4	//分辨率
#define TTX_RESOLUTION_720P				5	//分辨率
#define TTX_RESOLUTION_1080P			6	//分辨率

#ifdef WIN32

	#pragma warning(disable:4786)
	#include <WINSOCK2.H>
	#include <WINDOWS.H>
	
	#define _u64long unsigned __int64


	#define snprintf _snprintf
	#define _strncasecmp strnicmp
	#define _strcasecmp stricmp

#else

	#define _u64long unsigned long long

	#include <netinet/in.h>
	#include <string.h>

	#define _strncasecmp strncasecmp
	#define _strcasecmp strcasecmp

	
#endif

#ifndef NULL
	#define NULL 0
#endif	

#endif
