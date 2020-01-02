#ifndef _LIB_CLIENT_CONTROL_API_H_
#define _LIB_CLIENT_CONTROL_API_H_

#define LIBCLIENTCONTROL_EXPORTS
#ifdef LIBCLIENTCONTROL_EXPORTS
#define CLIENT_CONTROL_API __declspec(dllexport)
#else
#define CLIENT_CONTROL_API __declspec(dllimport)
#endif

#define APICALL WINAPI

#ifdef __cplusplus
extern "C" {
#endif

	//CP == CONTROL_CLIENT
	//显示loading窗口
//	CLIENT_CONTROL_API int APICALL CC_ShowDlgLoading(CString str, UINT nType=MB_OKCANCEL);
	//显示msg窗口
	CLIENT_CONTROL_API int APICALL CC_ShowDlgMsg(CString str, UINT nType=MB_OKCANCEL);

#ifdef __cplusplus
};
#endif

#endif