#ifndef _OBJPOOL_H_
#define _OBJPOOL_H_

#include <list>
#include <map>
#include "safedef.h"

const unsigned int MaxObjNum = 1024;


/*
	对象池，保存一个单向链表，需要时直接从缓存中取对象
	2007-12-20  当池中的对象不足时，再重新分配一组对象
*/
using namespace std;
template<typename T> class CObjPool
{
private:
	typedef map<T*, T*>	mapTObj;
	typedef typename CObjPool<T>::mapTObj::iterator	mapTIter;
	typedef std::list<T*>		lstTObj;
	typedef typename CObjPool<T>::lstTObj::iterator	iterTObj;

public: 
	CObjPool(unsigned int uiObjNum, unsigned int uiMaxFree = MaxObjNum);
	virtual ~CObjPool(void);

private:
	CObjPool();

public:
	T*		Alloc();
	void	Free(T*);
	int		GetAllCount();
	int		GetFreeCount();

private:
	void	NewObj(unsigned int uiObjNum);
	void	DelObj();
	void	Manage(unsigned int uiMaxFreeCount);

private:
	CRITICAL_SECTION m_cs;
	mapTObj	m_mapAllTObj;
	lstTObj	m_lstFreeTObj;
	unsigned int m_uiAllocNum;
	unsigned int m_uiMaxFree;
	DWORD	m_dwLastMgrTime;
};
 

template<typename T>CObjPool<T>::CObjPool(unsigned int uiObjNum, unsigned int uiMaxFree)
{
	InitializeCriticalSection(&m_cs);
	m_uiAllocNum = uiObjNum;
	m_uiMaxFree = uiMaxFree;
	NewObj(uiObjNum);
	m_dwLastMgrTime = GetTickCount();
}


template<typename T> CObjPool<T>::~CObjPool(void)
{
	DelObj();
	DeleteCriticalSection(&m_cs);
}


template<typename T> T* CObjPool<T>::Alloc()
{
	EnterCriticalSection(&m_cs);
	if (m_lstFreeTObj.size() <= 0)
	{
		NewObj(m_uiAllocNum);
	}

	iterTObj iter = m_lstFreeTObj.begin();
	T* pTObj = (*iter);
	m_lstFreeTObj.erase(iter);
	LeaveCriticalSection(&m_cs);
	return pTObj;
}

template<typename T> void CObjPool<T>::Free(T* pTObj)
{ 
	EnterCriticalSection(&m_cs);
	m_lstFreeTObj.push_front(pTObj);
	LeaveCriticalSection(&m_cs);

	if (TIMEIsTimeOut(m_dwLastMgrTime, 300000)) {
		Manage(m_uiMaxFree);
		m_dwLastMgrTime = GetTickCount();
	}
}

template<typename T> int CObjPool<T>::GetAllCount()
{
	int nFreeCount = 0;
	EnterCriticalSection(&m_cs);
	nFreeCount = m_mapAllTObj.size();
	LeaveCriticalSection(&m_cs);
	return nFreeCount;
}

template<typename T> int CObjPool<T>::GetFreeCount()
{
	int nFreeCount = 0;
	EnterCriticalSection(&m_cs);
	nFreeCount = m_lstFreeTObj.size();
	LeaveCriticalSection(&m_cs);
	return nFreeCount;
}

template<typename T> void CObjPool<T>::Manage(unsigned int uiMaxFreeCount)
{
	EnterCriticalSection(&m_cs);
	unsigned int nFreeCount = m_lstFreeTObj.size();
	if (nFreeCount > uiMaxFreeCount)
	{
		int nEraseCount = nFreeCount - uiMaxFreeCount;
		for (int i = 0; i < nEraseCount; ++ i) {
			iterTObj iter = m_lstFreeTObj.begin();
			T* pTObj = (*iter);
			m_lstFreeTObj.erase(iter);

			mapTIter iterFind = m_mapAllTObj.find(pTObj);
			if (iterFind != m_mapAllTObj.end())
			{
				m_mapAllTObj.erase(iterFind);
			}
			SAFE_DELETE_OBJECT(pTObj);
		}
	}
	LeaveCriticalSection(&m_cs);
}

template<typename T> void CObjPool<T>::NewObj(unsigned int uiObjNum)
{
	EnterCriticalSection(&m_cs);
	for (unsigned int i = 0; i < uiObjNum; ++ i)
	{
		T* pNewObj = new T;
		m_mapAllTObj.insert(mapTObj::value_type(pNewObj, pNewObj));
		m_lstFreeTObj.push_back(pNewObj);
	}
	
	LeaveCriticalSection(&m_cs);
};

template<typename T> void CObjPool<T>::DelObj()
{
	EnterCriticalSection(&m_cs);
	mapTIter iterB = m_mapAllTObj.begin();
	mapTIter iterE = m_mapAllTObj.end();
	while(iterB != iterE)
	{
		T* pNewObj = (*iterB).first;
		delete pNewObj; pNewObj = NULL;
		++ iterB;
	}
	m_mapAllTObj.clear();
	m_lstFreeTObj.clear();
	
	LeaveCriticalSection(&m_cs);
};

#endif