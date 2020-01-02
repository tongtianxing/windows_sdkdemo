#include "stdafx.h"
#include "MutexLock.h"

CMutexLock::CMutexLock()
{
	InitializeCriticalSection(&m_mutex);
}

CMutexLock::~CMutexLock()
{
	DeleteCriticalSection(&m_mutex);
}			

void CMutexLock::Lock() 		
{	
	EnterCriticalSection(&m_mutex); 
}

void CMutexLock::Unlock() 	
{	
	LeaveCriticalSection(&m_mutex); 
}

CAutoLock::CAutoLock(CMutexLock& Mutex)
{
	m_pMutex = &Mutex;
	if (m_pMutex != NULL)
	{
		m_pMutex->Lock();
	}
}

CAutoLock::~CAutoLock()
{
	Release();
}

CAutoLock::CAutoLock()
{
	m_pMutex = NULL;
}