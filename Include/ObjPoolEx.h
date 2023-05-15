#ifndef _OBJPOOLEX_H_
#define _OBJPOOLEX_H_

#include <list>
#include <map>
#include "StaticObject.h"
#include "safedef.h"

//const unsigned int MaxObjNumEx = 1024;


/*
	对象池扩展类，保存一个单向链表，需要时直接从缓存中取对象
	2012-7-20  当池中的对象不足时，再重新分配一组对象

*/
class CObjBase
{
public:
	CObjBase(){}
	virtual ~CObjBase(){}

	virtual BOOL Init() { return TRUE; }
	virtual BOOL UnInit() { return TRUE; }
};

template<typename CObjBase> class CObjPoolEx : public CStaticObject< typename CObjPoolEx<CObjBase> >	//此处> >中间必须有空格,否则vc6编译识别成">>" hw2014-4-18
{
private:
	typedef std::map<CObjBase*, CObjBase*>	mapTObj;
	typedef typename CObjPoolEx<CObjBase>::mapTObj::iterator	mapTIter;

	typedef std::list<CObjBase*>		lstTObj;
	typedef typename CObjPoolEx<CObjBase>::lstTObj::iterator	iterTObj;

public: 
	CObjPoolEx();
	virtual ~CObjPoolEx(void);

public:
	CObjBase*		Alloc();
	void	Free(CObjBase*);

private:
	void	NewObj(unsigned int uiObjNum);
	void	DelObj();
	void	Manage(unsigned int uiMaxCount);

private:
	CRITICAL_SECTION m_cs;
	mapTObj	m_mapAllTObj;
	lstTObj	m_lstFreeTObj;
	unsigned int m_uiAllocNum;
	unsigned int m_uiMaxFree;
	DWORD	m_dwLastMgrTime;
};


template<typename CObjBase>CObjPoolEx<CObjBase>::CObjPoolEx()
{
	InitializeCriticalSection(&m_cs);
	m_uiAllocNum = 32;
	m_uiMaxFree = 128;
	NewObj(m_uiAllocNum);
	m_dwLastMgrTime = GetTickCount();
}


template<typename CObjBase> CObjPoolEx<CObjBase>::~CObjPoolEx(void)
{
	DelObj();
	DeleteCriticalSection(&m_cs);
}


template<typename CObjBase> CObjBase* CObjPoolEx<CObjBase>::Alloc()
{
	EnterCriticalSection(&m_cs);
	if (m_lstFreeTObj.size() <= 0)
	{
		NewObj(m_uiAllocNum);
	}
	
	iterTObj iter = m_lstFreeTObj.begin();
	CObjBase* pTObj = (*iter);
	m_lstFreeTObj.erase(iter);
	LeaveCriticalSection(&m_cs);
	if(pTObj->Init())
	{
		return pTObj;
	}
	else
	{
		Free(pTObj);
		return NULL;
	}
}

template<typename CObjBase> void CObjPoolEx<CObjBase>::Free(CObjBase* pTObj)
{ 
	EnterCriticalSection(&m_cs);
	m_lstFreeTObj.push_front(pTObj);
	pTObj->UnInit();
	LeaveCriticalSection(&m_cs);

	if (TIMEIsTimeOut(m_dwLastMgrTime, 300000)) {
		Manage(m_uiMaxFree);
		m_dwLastMgrTime = GetTickCount();
	}
};

template<typename CObjBase> void CObjPoolEx<CObjBase>::Manage(unsigned int uiMaxCount)
{
	EnterCriticalSection(&m_cs);
	int nFreeCount = (int)m_lstFreeTObj.size();
	if (nFreeCount > (int)uiMaxCount)
	{
		int nEraseCount = nFreeCount - uiMaxCount;
		for (int i = 0; i < nEraseCount; ++ i) {
			iterTObj iter = m_lstFreeTObj.begin();
			CObjBase* pTObj = (*iter);
			m_lstFreeTObj.erase(iter);
			
			mapTIter iterFind = m_mapAllTObj.find(pTObj);
			if (iterFind != m_mapAllTObj.end())
			{
				m_mapAllTObj.erase(iterFind);
			}
			SAFE_DELETE_OBJECT(pTObj);
			
			//			else
			//			{
			//				ASSERT(FALSE);
			//			}
		}
	}
	LeaveCriticalSection(&m_cs);
}


template<typename CObjBase> void CObjPoolEx<CObjBase>::NewObj(unsigned int uiObjNum)
{
// 	if (uiObjNum == 0)
// 	{
// 		uiObjNum = 1024;
// 	}

	EnterCriticalSection(&m_cs);
	for (unsigned int i = 0; i < uiObjNum; ++ i)
	{
		CObjBase* pNewObj = new CObjBase;
		m_mapAllTObj.insert(mapTObj::value_type(pNewObj, pNewObj));
		m_lstFreeTObj.push_back(pNewObj);
		//++m_uiAllocNum;
	}
	
	LeaveCriticalSection(&m_cs);
};

template<typename CObjBase> void CObjPoolEx<CObjBase>::DelObj()
{
	EnterCriticalSection(&m_cs);
	mapTIter iterB = m_mapAllTObj.begin();
	mapTIter iterE = m_mapAllTObj.end();
	while(iterB != iterE)
	{
		CObjBase* pNewObj = (*iterB).first;
		delete pNewObj; pNewObj = NULL;
		++ iterB;
	}
	m_mapAllTObj.clear();
	m_lstFreeTObj.clear();
	
	LeaveCriticalSection(&m_cs);
};

#endif