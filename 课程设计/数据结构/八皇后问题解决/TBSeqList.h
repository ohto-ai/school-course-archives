#pragma once

// 头文件保护
#ifndef THATBOY_SEQLIST
#define THATBOY_SEQLIST

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include <initializer_list>
#include <memory.h>	// TODO
#include <stdexcept>
#include <typeinfo>
#include <algorithm>

#if THATBOY_DEBUG
#include <iostream>
#define _DEBUG_ECHO_CLASS_NAME(STRUCT_INFO) std::cout << "\rthatboy-Debug:" << typeid(*this).name() << "[" << this << "] " << STRUCT_INFO << std::endl;
#else
#define _DEBUG_ECHO_CLASS_NAME(STRUCT_INFO)
#endif // !THATBOY_DEBUG


namespace thatboy
{
	// 顺序表	
	template <typename T>
	class TBSeqList
	{
		/*
		对于执行失败的操作，如查询或者删除时找不到指定元素，一般返回list的长度size
		*/
	public:
		// 构造
		TBSeqList();									// 默认构造
		TBSeqList(const TBSeqList&);					// 拷贝构造
		TBSeqList(const T[], size_t);					// 数组构造
		TBSeqList(const T&, size_t);					// 构造指定数量的同值元素
		TBSeqList(const std::initializer_list<T>&);		// 初始化列表构造
	public:
		// 析构
		virtual ~TBSeqList();
	public:
		// 赋值
		virtual TBSeqList& Assign(const TBSeqList&);				// 赋值
		virtual TBSeqList& Assign(const T[], size_t);				// 赋值
		virtual TBSeqList& Assign(const std::initializer_list<T>&);	// 赋值
		virtual TBSeqList& Append(const TBSeqList&);				// 追加
		virtual TBSeqList& Append(const T[], size_t);				// 追加
		virtual TBSeqList& Append(const std::initializer_list<T>&);	// 追加

		// 交换
		virtual TBSeqList& Swap(TBSeqList&);								// 交换
		virtual TBSeqList& Reverse(size_t off = 0, size_t count = npos);	// 反转

		// 添加
		void Insert(size_t, const T&);					// 插入到指定位置之前
		void Insert(size_t, const TBSeqList&);			// 插入到指定位置之前
		void PushBack(const T&);						// 添加到末尾
		void PushBack(const TBSeqList&);				// 添加到末尾
		void PushFront(const T&);						// 添加到开头
		void PushFront(const TBSeqList&);				// 添加到开头

		// 删除
		size_t Erase(size_t);							// 移除指定位置元素
		size_t Erase(size_t, size_t);					// 移除指定区域元素（前闭后开）
		void PopFront();								// 移除首个元素
		void PopBack();									// 移除末尾元素

		size_t RemoveFirst(const T&);					// 移除首个同值元素
		size_t Remove(const T&);						// 移除同值元素
		template<typename FunT>
		size_t RemoveIf(FunT);							// 移除所有满足条件的元素

		size_t ReplaceFirst(const T&, const T&);		// 替换首个同值元素
		size_t Replace(const T&, const T&);				// 替换同值元素
		template<typename FunT>
		size_t ReplaceIf(FunT, const T&);				// 替换所有满足条件的元素

		void Clear();									// 移除所有元素
		size_t ShrinkToFit();								// 缩减容器容量至刚好容纳元素
		size_t Reserve(size_t);							// 预留容量

		T& Front();										// 返回起始元素
		const T& Front()const;							// 返回起始元素
		T& Back();										// 返回末尾元素
		const T& Back()const;							// 返回末尾元素
		size_t Size()const;								// 返回当前元素数量
		size_t Capacity()const;							// 返回当前容量
		bool Empty()const;								// 返回是否为空
		T& operator [](size_t);							// 返回元素引用
		const T& operator [](size_t)const;				// 返回元素引用
		const T* Data()const;							// 返回C风格数组

		size_t Search(const T&, size_t);				// 查询元素位置
		template<typename FunT>
		size_t SearchIf(FunT, size_t);					// 查询符合条件的元素位置
		

		// 运算符
		TBSeqList& operator = (const TBSeqList&);		// 赋值
		TBSeqList& operator +=(const TBSeqList&);		// 连接

		bool operator ==(const TBSeqList&)const;		// 对比元素相等
		bool operator !=(const TBSeqList&)const;		// 对比元素不等

		// STL需要
		T* begin()
		{
			return data;
		}
		const T* begin()const
		{
			return data;
		}
		T* end()
		{
			return data + size;
		}
		const T* end()const
		{
			return data + size;
		}

	protected:
		// 内存扩充
		virtual bool AutoExtendCapacity(int);			// 检查内存并自动扩充

		virtual bool Destory();		// 销毁
	protected:
		// 成员
		size_t size = 0;								// 元素数量
		size_t capacity = 0;							// 当前容量
		T* data = nullptr;								// 元素

		constexpr static size_t npos = static_cast<size_t>(-1);
	};

	// 优先顺序表	
	template <typename T
		, typename CompPr = std::greater<T>>
	class TBPrioritySeqList
		: protected TBSeqList<T>
	{
		/*
		对于执行失败的操作，如查询或者删除时找不到指定元素，一般返回list的长度size
		*/
	public:
		// 构造
		TBPrioritySeqList();									// 默认构造
		TBPrioritySeqList(const TBSeqList<T>&);					// 拷贝构造
		TBPrioritySeqList(const TBPrioritySeqList&);			// 拷贝构造
		TBPrioritySeqList(const T[], size_t);					// 数组构造
		TBPrioritySeqList(const T&, size_t);					// 构造指定数量的同值元素
		TBPrioritySeqList(const std::initializer_list<T>&);		// 初始化列表构造
	public:
		// 析构
		virtual ~TBPrioritySeqList();
	public:
		// 赋值
		virtual TBPrioritySeqList& Assign(const TBPrioritySeqList&);		// 赋值
		virtual TBPrioritySeqList& Assign(const T[], size_t);				// 赋值
		virtual TBPrioritySeqList& Assign(const std::initializer_list<T>&);	// 赋值

		// 交换
		virtual TBPrioritySeqList& Swap(TBPrioritySeqList&);				// 交换

		// 添加
		void Push(const T&);					// 添加
		void Push(const TBPrioritySeqList&);	// 添加
		// 删除
		size_t Erase(size_t);							// 移除指定位置元素
		size_t Erase(size_t, size_t);					// 移除指定区域元素（前闭后开）
		void PopFront();								// 移除首个元素
		void PopBack();									// 移除末尾元素
		size_t RemoveFirst(const T&);					// 移除首个同值元素
		size_t Remove(const T&);						// 移除同值元素
		template<typename FunT>
		void RemoveIf(FunT);							// 移除所有满足条件的元素
		void Clear();									// 移除所有元素
		void ShrinkToFit();								// 缩减容器容量至刚好容纳元素

		const T& Front()const;							// 返回起始元素
		const T& Back()const;							// 返回末尾元素
		size_t Size()const;								// 返回当前元素数量
		size_t Capacity()const;							// 返回当前容量
		bool Empty()const;								// 返回是否为空
		const T& operator [](size_t)const;				// 返回元素引用
		const T* Data()const;							// 返回C风格数组
		size_t Search(const T&);						// 查询首个元素位置
		template <typename FunT>
		size_t Search(const T&, FunT FunEqu);			// 查询首个元素位置

		// 运算符
		TBPrioritySeqList& operator = (const TBPrioritySeqList&);		// 赋值
		TBPrioritySeqList& operator +=(const TBPrioritySeqList&);		// 连接

		bool operator ==(const TBPrioritySeqList&)const;		// 对比元素相等
		bool operator !=(const TBPrioritySeqList&)const;		// 对比元素不等

		// STL需要
		T* begin()
		{
			return TBSeqList<T>::begin();
		}
		const T* begin()const
		{
			return TBSeqList<T>::begin();
		}
		T* end()
		{
			return TBSeqList<T>::end();
		}
		const T* end()const
		{
			return  TBSeqList<T>::end();
		}
		constexpr static size_t npos = static_cast<size_t>(-1);
	};
#pragma region TBSeqList

#pragma region 顺序表构造析构
	
	// 默认构造
	template<typename T>
	inline TBSeqList<T>::TBSeqList()
		: size(0)
		, capacity(0)
		, data(nullptr)
	{
		_DEBUG_ECHO_CLASS_NAME("默认构造");
	}

	// 拷贝构造
	template<typename T>
	inline TBSeqList<T>::TBSeqList(const TBSeqList& list)
		: size(list.size)
		, capacity(list.size)
		, data((T*)calloc(capacity, sizeof(T)))
	{
		for (size_t i = 0; i < Size(); ++i)
			new(data + i) T(list[i]);	// 构造
		_DEBUG_ECHO_CLASS_NAME("拷贝构造")
	}

	// 数组构造
	template<typename T>
	inline TBSeqList<T>::TBSeqList(const T list[], size_t n)
		: size(n)
		, capacity(n)
		, data((T*)calloc(capacity, sizeof(T)))
	{
		for (size_t i = 0; i < Size(); ++i)
			new(data + i) T(list[i]);	// 构造
		_DEBUG_ECHO_CLASS_NAME("数组构造");
	}

	// 构造指定数量的同值元素
	template<typename T>
	inline TBSeqList<T>::TBSeqList(const T& t, size_t n)
		: size(n)
		, capacity(n)
		, data((T*)calloc(capacity, sizeof(T)))
	{
		for (size_t i = 0; i < Size(); ++i)
			new(data + i) T(t);	// 构造
		_DEBUG_ECHO_CLASS_NAME("同值构造");
	}

	// 初始化列表构造
	template<typename T>
	inline TBSeqList<T>::TBSeqList(const std::initializer_list<T>& list)
		: size(list.size())
		, capacity(list.size())
		, data((T*)calloc(capacity, sizeof(T)))
	{
		auto ptr = data;
		for (const auto& t : list)
			new(ptr++) T(t);
		_DEBUG_ECHO_CLASS_NAME("初始化列表构造");
	}

	// 析构
	template<typename T>
	inline TBSeqList<T>::~TBSeqList()
	{		
		_DEBUG_ECHO_CLASS_NAME("析构");
		Destory();
	}

#pragma endregion


	// 检查内存并自动扩充
	template<typename T>
	inline bool TBSeqList<T>::AutoExtendCapacity(int append_size)
	{
		if ((int)(size + append_size) > (int)capacity)
		{
			while (size + append_size > capacity)
			{
				capacity = capacity + capacity / 2 + 1;
			}

			auto old_data = data;
			data = (T*)calloc(capacity, sizeof(T));
			// 拷贝构造并析构
			for (size_t i = 0; i < Size(); ++i)
			{
				new(data + i) T(old_data[i]);
				old_data[i].~T();
			}
			free(old_data);

			_DEBUG_ECHO_CLASS_NAME("扩充长度" << Size() << "(+" << append_size << ')');
			return true;
		}
		return false;
	}
	template<typename T>
	inline bool TBSeqList<T>::Destory()
	{
		_DEBUG_ECHO_CLASS_NAME("销毁(-" << Size() << ')');
		// 析构元素
		for (size_t i = 0; i < Size(); ++i)
			data[i].~T();
		// 释放内存
		free(data);
		// 恢复成员值
		data = nullptr;
		size = 0;
		capacity = 0;

		return true;
	}

#pragma region 赋值
	// 赋值
	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Assign(const TBSeqList&list)
	{
		_DEBUG_ECHO_CLASS_NAME("TBSeqList赋值");
		if (capacity < list.Size())	// 内存不够
		{
			Destory();
			size = list.Size();
			capacity = list.Size();
			data = (T*)calloc(capacity, sizeof(T));
			for (size_t i = 0; i < Size(); ++i)
				new(data + i) T(list[i]);
		}
		else// 内存足够
		{
			for (int i = Size() > list.Size() ? (list.Size() - 1) : (Size() - 1); i >= 0; --i)	// 对象赋值
				data[i] = list[i];
			for (size_t i = list.Size(); i < Size(); ++i)	// 析构多余对象
				data[i].~T();
			for (size_t i = Size(); i < list.Size(); ++i)	// 构造新增数量对象
				new(data + i) T(list[i]);
			size = list.Size();
		}
		return *this;
	}

	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Assign(const T list[], size_t len)
	{
		_DEBUG_ECHO_CLASS_NAME("T[]赋值");
		if (capacity < len)
		{
			Destory();
			size = len;
			capacity = len;
			data = (T*)calloc(capacity, sizeof(T));
			for (size_t i = 0; i < Size(); ++i)
				new(data + i) T(list[i]);
		}
		else
		{
			for (int i = Size() > len ? (len - 1) : (Size() - 1); i >= 0; --i)	// 对象赋值
				data[i] = list[i];
			for (size_t i = len; i < Size(); ++i)	// 析构多余对象
				data[i].~T();
			for (size_t i = Size(); i < len; ++i)	// 构造新增数量对象
				new(data + i) T(list[i]);
			size = len;
		}
		return *this;
	}

	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Assign(const std::initializer_list<T>&list)
	{
		_DEBUG_ECHO_CLASS_NAME("初始化列表赋值");
		if (capacity < list.size())	// 内存不够
		{
			Destory();
			size = list.size();
			capacity = list.size();
			data = (T*)calloc(capacity, sizeof(T));

			auto ptr = data;
			for (auto& t : list)
				new(ptr++) T(t);
		}
		else// 内存足够
		{
			for (int i = Size() > list.size() ? (list.size() - 1) : (Size() - 1); i >= 0; --i)	// 对象赋值
				data[i] = list.begin()[i];
			for (size_t i = list.size(); i < Size(); ++i)	// 析构多余对象
				data[i].~T();
			for (size_t i = Size(); i < list.size(); ++i)	// 构造新增数量对象
				new(data + i) T(list.begin()[i]);
			size = list.size();
		}
		return *this;
	}

#pragma endregion

#pragma region 插入
	// 插入到指定位置之前
	template<typename T>
	inline void TBSeqList<T>::Insert(size_t pos, const T& t)
	{
		if (pos > Size())
			throw std::out_of_range("插入元素位置超出范围");

		_DEBUG_ECHO_CLASS_NAME("单元素插入" << pos);
		AutoExtendCapacity(1);
		if (Size() > 0)
		{
			new(data + Size()) T(Back());
			for (int i = Size() - 1; i > static_cast<int>(pos); --i)
				data[i] = data[i - 1];
			data[pos] = t;
		}
		else
		{
			new(data + 0) T(t);
		}
		++size;
	}

	// 插入到指定位置之前
	template<typename T>
	inline void TBSeqList<T>::Insert(size_t pos, const TBSeqList& list)
	{
		if (pos > Size())
			throw std::out_of_range("插入元素位置超出范围");

		_DEBUG_ECHO_CLASS_NAME("TBSeqList插入" << pos << ',' << list.Size());
		AutoExtendCapacity(list.Size());
		for (int i = list.Size() + Size() - 1; i >= static_cast<int>(pos + list.Size()); --i)	// 移动pos到Size()-1的对象
			new (data + i) T(data[i - list.Size()]);
		for (int i = Size() - 1; i >= static_cast<int>(pos); --i)		// 复制pos到Size()-1的对应对象
			data[i] = list[i - pos];
		for (int i = pos + list.Size() - 1; i >= Size(); --i)	// 构造Size()到pos+list.Size()-1的对应对象
			new (data + i) T(list[i - pos]);

		size += list.size;
	}

#pragma endregion
	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Append(const TBSeqList&list)
	{
		Insert(size, list);
		return *this;
	}

	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Append(const T list[], size_t len)
	{
		return Append(TBSeqList<T>(list, len));
	}

	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Append(const std::initializer_list<T>&list)
	{
		return Append(TBSeqList<T>(list));
	}

	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Swap(TBSeqList&list)
	{
		auto my_data = data;
		auto my_size = size;
		auto my_capacity = capacity;
		data = list.data;
		size = list.size;
		capacity = list.capacity;
		list.data = my_data;
		list.size = my_size;
		list.capacity = my_capacity;
		return *this;
	}

	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::Reverse(size_t off, size_t count)
	{
		if (off >= Size() || off + count > Size())
			throw(std::out_of_range("翻转时发生访问越界！"));
		_DEBUG_ECHO_CLASS_NAME("逆转" << '<' << off << ',' << count << '>');
		std::reverse(data + off, data + off + count);
		return *this;
	}

	// 添加到末尾
	template<typename T>
	inline void TBSeqList<T>::PushBack(const T&t)
	{
		Insert(size, t);
	}

	// 添加到末尾
	template<typename T>
	inline void TBSeqList<T>::PushBack(const TBSeqList&list)
	{
		Insert(size, list);
	}

	// 添加到开头
	template<typename T>
	inline void TBSeqList<T>::PushFront(const T&t)
	{
		Insert(0, t);
	}

	// 添加到开头
	template<typename T>
	inline void TBSeqList<T>::PushFront(const TBSeqList&list)
	{
		Insert(0, list);
	}

	// 移除指定位置元素
	template<typename T>
	inline size_t TBSeqList<T>::Erase(size_t pos)
	{
		if (pos >= Size())
			throw std::out_of_range("移除位置越界！");
		for (size_t i = pos; i < Size() - 1; ++i)
			data[i] = data[i + 1];
		Back().~T();
		--size;
		return pos;
	}

	// 移除指定区域元素（前闭后开）
	template<typename T>

	inline size_t TBSeqList<T>::Erase(size_t beg, size_t end)
	{
		if (beg > end || beg >= Size() || end > Size())
			throw std::out_of_range("移除区间越界！");
		for (size_t i = end; i < Size() - end + beg - 1; ++i)
			data[i] = data[i + 1];
		for (size_t i = Size() - end + beg - 1; i < Size(); ++i)
			data[i].~T();
		size -= end - beg + 1;
		return end;
	}

	// 移除首个元素
	template<typename T>
	inline void TBSeqList<T>::PopFront()
	{
		Erase(0);
	}

	// 移除末尾元素
	template<typename T>
	inline void TBSeqList<T>::PopBack()
	{
		Erase(size - 1);
	}

	// 移除首个同值元素
	template<typename T>
	inline size_t TBSeqList<T>::RemoveFirst(const T&t)
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (t == data[i])
			{
				return Erase(i);
			}
		}
		return size;
	}

	// 移除同值元素
	template<typename T>
	inline size_t TBSeqList<T>::Remove(const T&t)
	{
		size_t beg = size;
		size_t write, read;
		for (size_t i = 0; i < Size(); ++i)
		{
			if (t == data[i])
			{
				beg = i;
				break;
			}
		}
		for (write = beg, read = beg + 1; read < Size(); ++read)
		{
			if (t == data[read])
				;
			else
			{
				data[write] = data[read];
				++write;
			}
		}
		for (size_t i = write; i < Size(); ++i)
			data[i].~T();
		size = write;
		return size;
	}

	template<typename T>
	inline size_t TBSeqList<T>::ReplaceFirst(const T& pattern, const T& t)
	{
		for (size_t i = 0; i < Size(); ++i)
		{
			if (data[i] == pattern)
			{
				data[i] = t;
				return i;
			}
		}
	}

	template<typename T>
	inline size_t TBSeqList<T>::Replace(const T& pattern, const T& t)
	{	
		for (size_t i = 0; i < Size(); ++i)
			if (data[i] == pattern)
				data[i] = t;
		return size;
	}

	// 移除所有元素
	template<typename T>
	inline void TBSeqList<T>::Clear()
	{
		for (size_t i = 0; i < Size(); ++i)
			data[i].~T();
		size = 0;
	}

	// 缩减容器容量至刚好容纳元素
	template<typename T>
	inline size_t TBSeqList<T>::ShrinkToFit()
	{
		if (capacity > size)
		{
			auto old_data = data;
			capacity = size;
			data = (T*)calloc(capacity, sizeof(T));
			for (size_t i = 0; i < size; ++i)
			{
				data[i] = old_data[i];
				old_data[i].~T();
			}
			free(old_data);
		}
		return Capacity();
	}

	template<typename T>
	inline size_t TBSeqList<T>::Reserve(size_t cap)
	{
		if (cap > Capacity())
		{
			auto old_data = data;
			capacity = cap;
			data = (T*)calloc(capacity, sizeof(T));
			for (size_t i = 0; i < size; ++i)
			{
				data[i] = old_data[i];
				old_data[i].~T();
			}
			free(old_data);
		}
		return Capacity();
	}

	template<typename T>
	inline T& TBSeqList<T>::Front()
	{
		return data[0];
	}

	template<typename T>
	inline const T& TBSeqList<T>::Front() const
	{
		return data[0];
	}

	template<typename T>
	inline T& TBSeqList<T>::Back()
	{
		return data[size - 1];
	}

	template<typename T>
	inline const T& TBSeqList<T>::Back() const
	{
		return data[size - 1];
	}



	// 返回当前元素数量
	template<typename T>
	inline size_t TBSeqList<T>::Size()const
	{
		return size;
	}

	// 返回当前元素数量
	template<typename T>
	inline size_t TBSeqList<T>::Capacity()const
	{
		return capacity;
	}

	// 返回是否为空
	template<typename T>
	inline bool TBSeqList<T>::Empty()const
	{
		return size == 0;
	}

	// 返回元素引用
	template<typename T>
	inline T& TBSeqList<T>::operator[](size_t off)
	{
		return data[off];
	}

	template<typename T>
	inline const T& TBSeqList<T>::operator[](size_t off) const
	{
		return data[off];
	}

	// 返回C风格数组
	template<typename T>
	inline const T* TBSeqList<T>::Data()const
	{
		return data;
	}

	// 赋值
	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::operator=(const TBSeqList&list)
	{
		return Assign(list);
	}

	// 连接顺序表
	template<typename T>
	inline TBSeqList<T>& TBSeqList<T>::operator+=(const TBSeqList&list)
	{
		return Append(list);
	}

	// 判断元素相等
	template<typename T>
	inline bool TBSeqList<T>::operator==(const TBSeqList&list)const
	{
		if (Size() != list.Size())
			return false;
		for (size_t i = 0; i < Size(); ++i)
			if (data[i] != list.data[i])
				return false;
		return true;
	}

	// 判断元素不等
	template<typename T>
	inline bool TBSeqList<T>::operator!=(const TBSeqList&list)const
	{
		return !(*this == list);
	}

	// 移除所有满足条件的元素
	template<typename T>
	template<typename FunT>
	inline size_t TBSeqList<T>::RemoveIf(FunT Fun)
	{
		size_t beg = size;
		size_t write, read;
		for (size_t i = 0; i < Size(); ++i)
		{
			if (Fun(data[i]))
			{
				beg = i;
				break;
			}
		}
		for (write = beg, read = beg + 1; read < Size(); ++read)
		{
			if (Fun(data[read]))
				;
			else
			{
				// TODO
				memcpy(data + write, data + read, sizeof(T));
				++write;
			}
		}
		for (size_t i = write; i < Size(); ++i)
			data[i].~T();
		size = write;
		return size;
	}

	template<typename T>
	template<typename FunT>
	inline size_t TBSeqList<T>::ReplaceIf(FunT Fun, const T&t)
	{
		for (size_t i = 0; i < Size(); ++i)
			if (Fun(data[i]))
				data[i] = t;
		return size;
	}

	// 搜索
	template<typename T>
	inline size_t TBSeqList<T>::Search(const T& pattern, size_t beg)
	{
		for (size_t i = beg; i < Size(); ++i)
			if (data[i] == pattern)
				return i;
	}
	// 搜索
	template<typename T>
	template<typename FunT>
	inline size_t TBSeqList<T>::SearchIf(FunT Fun, size_t beg)
	{
		for (size_t i = beg; i < Size(); ++i)
			if (Fun(data[i]))
				return i;
	}

#pragma endregion
	template<typename T, typename CompPr>
	inline TBPrioritySeqList<T, CompPr>::TBPrioritySeqList()
		: TBSeqList<T>()
	{}
	template<typename T, typename CompPr>
	inline TBPrioritySeqList<T, CompPr>::TBPrioritySeqList(const TBSeqList<T>&list)
		: TBSeqList<T>(list)
	{
		std::sort(begin(), end());
	}
	template<typename T, typename CompPr>
	inline TBPrioritySeqList<T, CompPr>::TBPrioritySeqList(const TBPrioritySeqList&list)
		: TBSeqList<T>(list)
	{}
}

#endif // !THATBOY_SEQLIST