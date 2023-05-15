#ifndef _SAFE_DEF_H_
#define _SAFE_DEF_H_

#define SAFE_DELETE_OBJECT(p) if ((p) != NULL) {delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) if ((p) != NULL) {delete [] (p); (p) = NULL;}
#define SAFE_CLOSE_HANDLE(p) if ((p) != NULL) {CloseHandle((p)); (p) = NULL;}
#define SAFE_CLOSE_SOCKET(p) if ((p) != INVALID_SOCKET) {closesocket((p)); (p) = INVALID_SOCKET;}
#define SAFE_DELETE_GDI_OBJ(p) if ((p) != NULL) { ::DeleteObject(p); (p) = NULL; }

#ifdef SAFE_RELEASE
#undef SAFE_RELEASE
#endif
#define SAFE_RELEASE(x)		{ if (x) (x)->Release(); (x) = NULL; }


#define SAFE_EXECURE_FUNC(Pointer, function) { auto p = Pointer; if (p) p->function; }
#define SAFE_EXECURE_FUNC_RET(Result, Pointer, function)	{ auto p = Pointer; if (p) Result = p->function; }

#if defined(__AFXWIN_H__)
inline static BOOL safe_PostMessage(void* p, UINT nMsg, WPARAM wParam = 0, LPARAM lParam = 0)
{
	if (p)
	{
		return ::PostMessage(reinterpret_cast<CWnd*>(p)->GetSafeHwnd(), nMsg, wParam, lParam);
	}
	return FALSE;
}

inline static LRESULT safe_SendMessage(void* p, UINT nMsg, WPARAM wParam = 0, LPARAM lParam = 0)
{
	if (p)
	{
		return ::SendMessage(reinterpret_cast<CWnd*>(p)->GetSafeHwnd(), nMsg, wParam, lParam);
	}
	return S_FALSE;
}

#define SAFE_PostMessage(...)	safe_PostMessage(__VA_ARGS__)
#define SAFE_SendMessage(...)	safe_SendMessage(__VA_ARGS__)
#endif


// ģ�庯��,�ͷ�LONG_PTR����Ķ���,��Ҫ������������
// ʾ������:
// class CTest;						//����һ����
// CTest* pTest = new CTest();			//new�����
// LONG_PTR lData = (LONG_PTR)pData;	//��ָ��ת��ΪLONG_PTR
// SAFE_DELETE_LONG_PTR<CTest>(lData);	//�ͷŶ������LONG_PTR
template <class T>
bool	SAFE_DELETE_LONG_PTR(LONG_PTR& lHandle)
{
	T* p = (T*)lHandle;
	if (p)
	{
		// 1.�ͷ�ָ��
		delete p;
		// 2.���LONG_PTR
		lHandle = NULL;
		return true;
	}
	return false;
}


//************************************
// Method:    safe_strncpy, safe_wcsncpy, safe_tcsncpy
// FullName:  safe_strncpy, safe_wcsncpy, safe_tcsncpy
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char(&dst)[nSize]
// Parameter: const char * src
//************************************
template <int nSize>
void safe_strncpy(char(&dst)[nSize], const char* src)
{
	//strncpy(dst, src, nSize - 1);
	strncpy_s(dst, src, nSize - 1);
}
template <int nSize>
void safe_strncpy_limit(char(&dst)[nSize], const char* src, int nSrcLen)
{
	if (nSrcLen > nSize - 1)
	{
		nSrcLen = nSize - 1;
	}
	strncpy_s(dst, src, nSrcLen);
}
template <int nSize>
void safe_wcsncpy(wchar_t(&dst)[nSize], const wchar_t* src)
{
	//strncpy(dst, src, nSize - 1);
	wcsncpy_s(dst, src, nSize - 1);
}

#ifdef _INC_TCHAR
template <int nSize>
void safe_tcsncpy(TCHAR(&dst)[nSize], const TCHAR* src)
{
	//strncpy(dst, src, nSize - 1);
	_tcsncpy_s(dst, src, nSize - 1);
}
#endif

#define SAFE_STRNCPY(...)	safe_strncpy(__VA_ARGS__)
#define SAFE_STRNCPY_LIMIT(...)	safe_strncpy_limit(__VA_ARGS__)

#define SAFE_WCSNCPY(...)	safe_wcsncpy(__VA_ARGS__)

#ifdef _INC_TCHAR
#define SAFE_TCSNCPY(...)	safe_tcsncpy(__VA_ARGS__)
#endif

/* SAFE_STRNCPYʹ��ʾ��

char arr[10];
// ��ʼ���ַ�����Ϊ0
SAFE_STRNCPY(arr, "ydl");	//������=ydl
SAFE_STRNCPY(arr, "ydl123456789");//������=ydl123456(9���ַ�)

*/

//************************************
// Method:    safe_memcpy
// FullName:  safe_memcpy
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char(&dst)[nSize]
// Parameter: const void * src
//************************************
template <int nSize>
void safe_memcpy(char(&dst)[nSize], const void* src)
{
	//memcpy(dst, src, nSize - 1);
	memcpy(dst, src, nSize - 1);
}
template <class T>
void safe_memcpy(T& dst, const T& src)
{
	memcpy(&dst, &src, sizeof(T));
}
#define SAFE_MEMCPY(...)	safe_memcpy(__VA_ARGS__)
/* SAFE_MEMCPYʹ��ʾ��
type v1;
type v2;
// �����󿽱��ڴ�,ע��:���ܴ�����ָ��
SAFE_MEMCPY(v1, v2);

char arr[10];
// ��ʼ���ַ�����Ϊ0
SAFE_MEMCPY(arr, "ydl");	//������=ydl
SAFE_MEMCPY(arr, "ydl123456789");//������=ydl123456(9���ַ�)

*/

//************************************
// Method:    safe_memset
// FullName:  safe_memset
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char(&dst)[nSize]
// Parameter: char c
//************************************
template <class T, int nSize>
void safe_memset(T(&dst)[nSize], int nVal = 0)
{
	memset(dst, nVal, nSize * sizeof(T));
}
template <class T>
void safe_memset(T& dst, int nVal = 0)
{
	// Ϊ�������ʹ����ָ�봫��,���Ƶ���ָ�볤�ȵĶ����ʼ�� [2020-4-24 ydl]
	static_assert(sizeof(T) != sizeof(void*), "safe_memset error! Cannot use pointer!");
	memset(&dst, nVal, sizeof(T));
}
#define SAFE_MEMSET(...)	safe_memset(__VA_ARGS__)
/* SAFE_MEMSETʹ��ʾ��
type arr[100];
// ��ʼ������Ϊ0
SAFE_MEMSET(arr);

type n;
// ��ʼ�����������ڴ�����Ϊ0,ע��:���󴫲β�Ҫȡ��ַ
SAFE_MEMSET(n);		//�����÷�:SAFE_MEMSET(&n);
*/



// ���ַ�����,תΪָ��+���ȵ�����
#define ARRAY_TO_PTS_SIZE(arr)	(arr), sizeof(arr)


#endif