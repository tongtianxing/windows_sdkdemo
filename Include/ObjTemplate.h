#pragma once
/*****************************************************************************
//容器模板函数
******************************************************************************/


#define Get1st(iter) ((iter).first)
#define Get2nd(iter) ((iter).second)

#define GetMapBegin1st(_Map) Get1st(*std::begin(_Map))
#define GetMapBegin2nd(_Map) Get2nd(*std::begin(_Map))

// 计算map容器first和second的字节长度
#define SizeofMap1st(_Map)	(sizeof(Get1st(*std::begin(_Map))))
#define SizeofMap2nd(_Map)	(sizeof(Get2nd(*std::begin(_Map))))

#define SizeofObject(_Obj)	(sizeof(*std::begin(_Obj)))

// 获取容器的数量,转为int类型
#define GetObjectSize(_Obj)		((int)(_Obj.size()))
#define GetPtrObjSize(_pObj)	((int)(_pObje->size()))

// vector转换指针
#define Vec2Pointer(_Vec)  ((_Vec.empty()) ? NULL : &_Vec[0])

// 将vector转换为指针和对象数量,表示两个参数
#define Vec2PointerAndSize(_Vec)	Vec2Pointer(_Vec), GetObjectSize(_Vec)
#if _MSC_VER >= 1600
// 以下宏用于std::map数据的处理,参数:map对象
// 解析map数据的类型
#define DECLTYPE(_Map)	decltype(*std::begin(_Map))
//#define DECLTYPER(_map)	(decltype(*_map.rbegin()))
// lambda函数,用于获取map的first值
#define FuncGet1st(_Map) [](DECLTYPE(_Map)& it) { return Get1st(it); }
// lambda函数,用于获取map的second值
#define FuncGet2nd(_Map) [](DECLTYPE(_Map)& it) { return Get2nd(it); }
// lambda函数,用于释放map的second的资源
#define FuncDelete2nd(_Map)  [](DECLTYPE(_Map)& it) { SAFE_DELETE_OBJECT(Get2nd(it)); }
// lambda函数,用于释放STL对象值
#define FuncDeleteObj(_Obj)  [](DECLTYPE(_Obj)& it) { SAFE_DELETE_OBJECT(it); }

// 模板函数,查找map对象的key对应的value,查找失败返回空值
// 适用于value为简单类型,使用默认为0的值
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

// 返回对象的地址,适用于value为结构体,或者某些构造消耗太多资源的
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

// 模板函数,查找map对象的key对应的value,查找成功返回true并填充值
// 适用于需要判断值是否存在并操作对应值
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

// 模板函数,判断某个值是否为map对象的key,查找成功返回true
// 适用于仅需要判断值是否存在的情况
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

// 模板函数,用来从map中删除一个字段并返回对象
// 主要用于指针类型的对象返回并释放,结构体请勿调用
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

// 释放map中的第二个对象值(不清空map)
#define DeleteAllMap2Obj(_Map)  std::for_each(std::begin(_Map), std::end(_Map), FuncDelete2nd(_Map)) 
// 释放容器对象(不清空容器)
#define DeleteAllObject(_Obj) std::for_each(std::begin(_Obj), std::end(_Obj), FuncDeleteObj(_Obj))

// 清空容器,并且释放容器申请的资源
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

// 拷贝数据,必须预先分配好内存
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
 * @Description: 插入数据时从小到大插入排序,一般用于vector容器
 * @param: obj:容器对象
 * @param: data:新插入的数据,默认为模板less<type>()
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
 * @Description: 插入数据时从大到小插入排序,一般用于vector容器
 * @param: obj:容器对象
 * @param: data:新插入的数据
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
// 将一个对象按字节流添加到vector<char>容器中
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