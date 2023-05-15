#pragma once
/*****************************************************************************
//����ģ�庯��
******************************************************************************/


#define Get1st(iter) ((iter).first)
#define Get2nd(iter) ((iter).second)

#define GetMapBegin1st(_Map) Get1st(*std::begin(_Map))
#define GetMapBegin2nd(_Map) Get2nd(*std::begin(_Map))

// ����map����first��second���ֽڳ���
#define SizeofMap1st(_Map)	(sizeof(Get1st(*std::begin(_Map))))
#define SizeofMap2nd(_Map)	(sizeof(Get2nd(*std::begin(_Map))))

#define SizeofObject(_Obj)	(sizeof(*std::begin(_Obj)))

// ��ȡ����������,תΪint����
#define GetObjectSize(_Obj)		((int)(_Obj.size()))
#define GetPtrObjSize(_pObj)	((int)(_pObje->size()))

// vectorת��ָ��
#define Vec2Pointer(_Vec)  ((_Vec.empty()) ? NULL : &_Vec[0])

// ��vectorת��Ϊָ��Ͷ�������,��ʾ��������
#define Vec2PointerAndSize(_Vec)	Vec2Pointer(_Vec), GetObjectSize(_Vec)
#if _MSC_VER >= 1600
// ���º�����std::map���ݵĴ���,����:map����
// ����map���ݵ�����
#define DECLTYPE(_Map)	decltype(*std::begin(_Map))
//#define DECLTYPER(_map)	(decltype(*_map.rbegin()))
// lambda����,���ڻ�ȡmap��firstֵ
#define FuncGet1st(_Map) [](DECLTYPE(_Map)& it) { return Get1st(it); }
// lambda����,���ڻ�ȡmap��secondֵ
#define FuncGet2nd(_Map) [](DECLTYPE(_Map)& it) { return Get2nd(it); }
// lambda����,�����ͷ�map��second����Դ
#define FuncDelete2nd(_Map)  [](DECLTYPE(_Map)& it) { SAFE_DELETE_OBJECT(Get2nd(it)); }
// lambda����,�����ͷ�STL����ֵ
#define FuncDeleteObj(_Obj)  [](DECLTYPE(_Obj)& it) { SAFE_DELETE_OBJECT(it); }

// ģ�庯��,����map�����key��Ӧ��value,����ʧ�ܷ��ؿ�ֵ
// ������valueΪ������,ʹ��Ĭ��Ϊ0��ֵ
template <class _MapType, class _KeyType>
auto FuncFindMap2nd(const _MapType& _Map, const _KeyType& key) -> decltype(_Map.begin()->second)
{
	auto IterF = _Map.find(key);
	if (IterF != _Map.end())
	{
		return IterF->second;
	}
	return _MapType::mapped_type();
}

// ���ض���ĵ�ַ,������valueΪ�ṹ��,����ĳЩ��������̫����Դ��
template <class _MapType, class _KeyType>
auto FuncFindMap2ndPts(_MapType& _Map, const _KeyType& key) -> decltype(&(_Map.begin()->second))
{
	auto IterF = _Map.find(key);
	if (IterF != _Map.end())
	{
		return &(IterF->second);
	}
	return NULL;
}

// ģ�庯��,����map�����key��Ӧ��value,���ҳɹ�����true�����ֵ
// ��������Ҫ�ж�ֵ�Ƿ���ڲ�������Ӧֵ
template <class _MapType, class _KeyType, class _ValueType>
bool FuncFindMap2ndValue(const _MapType& _Map, const _KeyType& key, _ValueType& Val)
{
	auto IterF = _Map.find(key);
	if (IterF != _Map.end())
	{
		Val = IterF->second;
		return true;
	}
	return false;
}

// ģ�庯��,�ж�ĳ��ֵ�Ƿ�Ϊmap�����key,���ҳɹ�����true
// �����ڽ���Ҫ�ж�ֵ�Ƿ���ڵ����
template <class _MapType, class _KeyType>
bool FuncIsMapKey(const _MapType& _Map, const _KeyType& key)
{
	auto IterF = _Map.find(key);
	if (IterF != _Map.end())
	{
		return true;
	}
	return false;
}

// ģ�庯��,������map��ɾ��һ���ֶβ����ض���
// ��Ҫ����ָ�����͵Ķ��󷵻ز��ͷ�,�ṹ���������
// template <class _MapType, class _KeyType>
// auto FuncMapErase(_MapType& _Map, const _KeyType& key) -> decltype((_Map.begin()->second))
// {
// 	_MapType::mapped_type ptr = _MapType::mapped_type();
// 	static_assert(sizeof(ptr) == sizeof(nullptr_t), "sizeof(ptr) == sizeof(nullptr_t)");
// 	auto IterF = _Map.find(key);
// 	if (IterF != _Map.end())
// 	{
// 		ptr = IterF->second;
// 		_Map.erase(IterF);
// 	}
// 	return ptr;
// }



#define FindMap2nd(_Map, _Key)	FuncFindMap2nd(_Map, _Key)
#define FindMap2ndPts(_Map, _Key)	FuncFindMap2ndPts(_Map, _Key)
#define FindMap2ndValue(_Map, _Key, _Val)	FuncFindMap2ndValue(_Map, _Key, _Val)
#define IsMapKey(_Map, _Key)	FuncIsMapKey(_Map, _Key)

#include <algorithm>

// �ͷ�map�еĵڶ�������ֵ(�����map)
#define DeleteAllMap2Obj(_Map)  std::for_each(std::begin(_Map), std::end(_Map), FuncDelete2nd(_Map)) 
// �ͷ���������(���������)
#define DeleteAllObject(_Obj) std::for_each(std::begin(_Obj), std::end(_Obj), FuncDeleteObj(_Obj))

// �������,�����ͷ������������Դ
//#define ClearObject(_Obj) { decltype(_Obj) __##_Obj; _Obj.swap(__##_Obj); /*__##_Obj.clear();*/  }
template <class T>
void ClearObject(T& obj)
{
	T __obj;
	obj.swap(__obj);
}
template <class T>
void ClearObject(T* pObj)
{
	if (pObj)
	{
		T __obj;
		(*pObj).swap(__obj);
	}
}

// ��������,����Ԥ�ȷ�����ڴ�
// #define Map1stToDes(_Map, _Des) std::transform((_Map).begin(), (_Map).end(), (_Des), FuncGet1st(_Map))
// #define Map2ndToDes(_Map, _Des) std::transform((_Map).begin(), (_Map).end(), (_Des), FuncGet2nd(_Map))
// 
// #define ObjToDes(_Obj, _Des) std::copy((_Obj).begin(), (_Obj).end(), _Des)

template <class _MapT, class _DesT>
size_t CopyMap1stToDes(_MapT& _Map, _DesT _Des)
{
	std::transform(std::begin(_Map), std::end(_Map), _Des, FuncGet1st(_Map));
	return _Map.size() * SizeofMap1st(_Map);
}

template <class _MapT, class _DesT>
size_t CopyMap2ndToDes(_MapT& _Map, _DesT _Des)
{
	std::transform(std::begin(_Map), std::end(_Map), _Des, FuncGet2nd(_Map));
	return _Map.size() * SizeofMap2nd(_Map);
}

template <class _ObjT, class _DesT>
size_t CopyObjectToDes(_ObjT& _Obj, _DesT _Des)
{
	std::copy(std::begin(_Obj), std::end(_Obj), _Des);
	return _Obj.size() * SizeofObject(_Obj);
}

#endif

/**
 * @Description: ��������ʱ��С�����������,һ������vector����
 * @param: obj:��������
 * @param: data:�²��������,Ĭ��Ϊģ��less<type>()
 * @return: void
 * @Author: 
 */
template <class ObjT, class _Ty>
void InsertSort(ObjT& obj, const _Ty& data)
{
	auto IterF = std::upper_bound(std::begin(obj), std::end(obj), data);
	obj.insert(IterF, data);
};

template <class ObjT, class _Ty, class _Pr>
void InsertSort_If(ObjT& obj, const _Ty& data, const _Pr& pfn)
{
	auto IterF = std::upper_bound(std::begin(obj), std::end(obj), data, pfn);
	obj.insert(IterF, data);
};

/**
 * @Description: ��������ʱ�Ӵ�С��������,һ������vector����
 * @param: obj:��������
 * @param: data:�²��������
 * @return: void
 * @Author: 
 */
template <class ObjT, class _Ty>
void InsertRSort(ObjT& obj, const _Ty& data)
{
	auto IterF = std::upper_bound(std::begin(obj), std::end(obj), data, std::greater<_Ty>());
	obj.insert(IterF, data);
};



#ifdef _VECTOR_
// ��һ�������ֽ�����ӵ�vector<char>������
template <class T>
void OBjInsertBufByObject(std::vector<char>& vecBuf, T& data)
{
	return OBjInsertBufByObject(vecBuf, &data);
}

template <class T>
void OBjInsertBufByObject(std::vector<char>& vecBuf, T* pData)
{
	if (pData)
	{
		vecBuf.insert(std::end(vecBuf), (char*)pData, (char*)(pData + 1));
	}
}
#endif // _VECTOR_