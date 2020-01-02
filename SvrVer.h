// SvrVer.h: interface for the CSvrVer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVRVER_H__0269EC9D_E240_4CBA_9766_4E9DF1E6E569__INCLUDED_)
#define AFX_SVRVER_H__0269EC9D_E240_4CBA_9766_4E9DF1E6E569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSvrVer : public CStaticObject<CSvrVer>
{
public:
	CSvrVer();
	virtual ~CSvrVer();

	//配置和获取服务器的版本
	void SetSvrVer(int nSvrVer);
	int GetSvrVer();
	
	//服务器版本判断接口
	bool IsSvrVerV6();		//v6版本服务器
	bool IsSvrVerV7();		//808(v7)版本
	
private:
	bool IsSvrVer(int nSvrVer);
private:
	int m_nSvrVer;

};

#endif // !defined(AFX_SVRVER_H__0269EC9D_E240_4CBA_9766_4E9DF1E6E569__INCLUDED_)
