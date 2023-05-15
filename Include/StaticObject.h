#pragma once


// CStaticObject类是线程安全的

#if _MSC_VER < 1900	//1900 是vs2015的版本

	template <class T>
	class CStaticObject
	{
	public:		
		static T * GetInstance()
		{
			return &m_Instance;
		}
	protected:
		static T m_Instance;
	};
	template <class T>
	T  CStaticObject<T>::m_Instance;


	// 简化版本:此版本非线程安全
	template <class T>
	class CStaticObjectSimple
	{
	public:
		static T* GetInstance()
		{
			static T s_Instance;
			return &s_Instance;
		}
	};

#else

	template <class T>
	class CStaticObject
	{
	public:		
		static T * GetInstance()
		{
			// C++11 静态局部变量是线程安全的
			static T s_Instance;
			return &s_Instance;
		}
	};

#define CStaticObjectSimple	CStaticObject


#endif