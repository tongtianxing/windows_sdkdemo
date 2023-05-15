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


// 模板函数,释放LONG_PTR保存的对象,需要传入对象的类型
// 示例代码:
// class CTest;						//声明一个类
// CTest* pTest = new CTest();			//new类对象
// LONG_PTR lData = (LONG_PTR)pData;	//将指针转换为LONG_PTR
// SAFE_DELETE_LONG_PTR<CTest>(lData);	//释放对象并清空LONG_PTR
template <class T>
bool	SAFE_DELETE_LONG_PTR(LONG_PTR& lHandle)
{
	T* p = (T*)lHandle;
	if (p)
	{
		// 1.释放指针
		delete p;
		// 2.清空LONG_PTR
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

/* SAFE_STRNCPY使用示例

char arr[10];
// 初始化字符数组为0
SAFE_STRNCPY(arr, "ydl");	//拷贝后=ydl
SAFE_STRNCPY(arr, "ydl123456789");//拷贝后=ydl123456(9个字符)

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
/* SAFE_MEMCPY使用示例
type v1;
type v2;
// 按对象拷贝内存,注意:不能传对象指针
SAFE_MEMCPY(v1, v2);

char arr[10];
// 初始化字符数组为0
SAFE_MEMCPY(arr, "ydl");	//拷贝后=ydl
SAFE_MEMCPY(arr, "ydl123456789");//拷贝后=ydl123456(9个字符)

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
	// 为避免对象使用了指针传参,限制等于指针长度的对象初始化 [2020-4-24 ydl]
	static_assert(sizeof(T) != sizeof(void*), "safe_memset error! Cannot use pointer!");
	memset(&dst, nVal, sizeof(T));
}
#define SAFE_MEMSET(...)	safe_memset(__VA_ARGS__)
/* SAFE_MEMSET使用示例
type arr[100];
// 初始化数组为0
SAFE_MEMSET(arr);

type n;
// 初始化任意对象的内存数据为0,注意:对象传参不要取地址
SAFE_MEMSET(n);		//错误用法:SAFE_MEMSET(&n);
*/



// 将字符数组,转为指针+长度的数据
#define ARRAY_TO_PTS_SIZE(arr)	(arr), sizeof(arr)


#endif