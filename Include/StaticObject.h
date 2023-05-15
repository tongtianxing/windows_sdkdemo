#pragma once


// CStaticObject�����̰߳�ȫ��

#if _MSC_VER < 1900	//1900 ��vs2015�İ汾

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


	// �򻯰汾:�˰汾���̰߳�ȫ
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
			// C++11 ��̬�ֲ��������̰߳�ȫ��
			static T s_Instance;
			return &s_Instance;
		}
	};

#define CStaticObjectSimple	CStaticObject


#endif