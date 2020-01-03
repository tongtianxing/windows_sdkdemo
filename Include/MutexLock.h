#ifndef _MUTEX_LOCK_H_
#define _MUTEX_LOCK_H_

class CMutexLock
{
public:
	CMutexLock();
	virtual ~CMutexLock();

private:
	CMutexLock(const CMutexLock& );
	CMutexLock& operator = (const CMutexLock& );

public:
	void		Lock();
	void		Unlock();
private:
	CRITICAL_SECTION	 m_mutex;
};

class CAutoLock
{
public:
	CAutoLock(CMutexLock& Mutex);
	virtual ~CAutoLock();
	
public:
	void		Release() 
	{
		if (m_pMutex != NULL)
		{
			m_pMutex->Unlock();
			m_pMutex = NULL;
		}
	}
	
private:
	CAutoLock();
	CAutoLock(const CAutoLock& );
	CAutoLock& operator = (const CAutoLock& );
	
private:
	CMutexLock*		m_pMutex;
};

#endif

