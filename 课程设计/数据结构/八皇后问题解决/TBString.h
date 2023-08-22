#pragma once

// 头文件保护
#ifndef THATBOY_STRING_H
#define THATBOY_STRING_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS

#include <initializer_list>
#include <memory.h>	// TODO
#include <stdexcept>
#include <typeinfo>
#include <algorithm>
#include "TBSeqList.h"

#if THATBOY_DEBUG
#include <iostream>
#define _DEBUG_ECHO_CLASS_NAME(STRUCT_INFO) std::cout << "\rthatboy-Debug:" << typeid(*this).name() << "[" << this << "] " << STRUCT_INFO << std::endl;
#else
#define _DEBUG_ECHO_CLASS_NAME(STRUCT_INFO)
#endif // !THATBOY_DEBUG

namespace thatboy
{
#ifndef UNICODE
		using tchar = char;
#ifndef TEXT
#define TEXT(quote) quote
#endif // !TEXT

#else
		using tchar = wchar_t;
#ifndef TEXT
#define TEXT(quote) L##quote
#endif // !TEXT

#endif
	class TBString
	{

	public:
		TBString();									// 默认构造
		TBString(tchar);							// 字符构造
		TBString(const TBString&);					// 拷贝构造
		TBString(const tchar[]);					// 字符串构造	
		TBString(const tchar[], size_t);			// 字符数组构造	

		virtual ~TBString();

		TBString& Assign(const TBString&);			// 赋值
		TBString& Assign(const tchar[]);			// 赋值
		TBString& Assign(tchar);					// 赋值

		TBString& Append(const TBString&);			// 追加
		TBString& Append(const tchar[]);			// 追加
		TBString& Append(tchar);					// 追加
		TBString& Append(int);						// 追加

		TBString& operator = (const TBString&);		// 赋值
		TBString& operator = (const tchar[]);		// 赋值
		TBString& operator = (tchar);				// 赋值

		TBString& operator +=(const TBString&);		// 追加
		TBString& operator +=(const tchar[]);		// 追加
		TBString& operator +=(tchar);				// 追加
		TBString& operator +=(int);					// 追加

		TBString operator + (const TBString&)const;	// 加法
		TBString operator + (const tchar[])const;	// 加法
		TBString operator + (tchar)const;			// 加法
		TBString operator + (int)const;				// 加法

		void Insert(size_t, const TBString&);		// 插入
		void Insert(size_t, const tchar[]);			// 插入
		void Insert(size_t, tchar);					// 插入

		size_t Remove(tchar);						// 移除

		size_t Erase(size_t);
		size_t Erase(size_t, size_t);

		void PushFront(const tchar&);				// 添加到开头
		void PushFront(const TBString&);			// 添加到开头
		void PushBack(const tchar&);				// 添加到末尾
		void PushBack(const TBString&);				// 添加到末尾
		void PopFront();							// 移除开头元素
		void PopBack();								// 移除末尾元素

		tchar& Front();								// 返回末尾元素
		const tchar& Front()const;					// 返回末尾元素
		tchar& Back();								// 返回末尾元素
		const tchar& Back()const;					// 返回末尾元素

		TBString SubStr(size_t off = 0, size_t count = npos)const;	// 返回子串
		TBString& Reverse(size_t off = 0, size_t count = npos);		// 逆转串

		size_t Search(const TBString& pattern, size_t beg = 0);		// 搜索
		template<typename FunT>
		size_t SearchIf(FunT, size_t beg = 0);						// 搜索

		size_t ReplaceFirst(const TBString&, const TBString&);		// 替换
		size_t Replace(const TBString&, const TBString&);			// 替换
		//template<typename FunT>
		//size_t ReplaceIf(FunT, const TBString&);					// 替换

		bool Empty()const;							// 返回是否为空
		void Clear();								// 清除内容

		const tchar* C_Str()const;					// 返回C风格字符串
		tchar& At(size_t off);						// 安全地访问指定元素
		const tchar& At(size_t off)const;			// 安全地访问指定元素
		size_t Len()const;							// 字符串长度
		size_t Size()const;							// 字符串长度
		size_t Capacity()const;						// 当前容量

		tchar& operator [](size_t);
		const tchar& operator [](size_t)const;

		char* begin()
		{
			return data;
		}
		char* end()
		{
			return data + size;
		}
		const char* begin()const
		{
			return data;
		}
		const char* end()const
		{
			return data + size;
		}
	protected:
		// 内存扩充
		virtual bool AutoExtendCapacity(int);			// 检查内存并自动扩充

	protected:
		// 成员
		size_t size = 0;								// 元素数量
		size_t capacity = 0;							// 当前容量
		tchar* data = nullptr;							// 元素

		constexpr static size_t npos = static_cast<size_t>(-1);
	};
	TBString To_TBString(int);				// 转换为TBString
	TBString To_TBString(tchar);			// 转换为TBString
	TBString To_TBString(const tchar[]);	// 转换为TBString
	TBString To_TBString(double);			// 转换为TBString

	size_t StrLen(const char* str);			// 快速统计长度
	size_t StrLen(const wchar_t* str);		// 快速统计长度


	// 默认构造
	inline TBString::TBString()
		: size(0)
		, capacity(1)
		, data(new tchar[capacity])
	{
		data[0] = '\0';
		_DEBUG_ECHO_CLASS_NAME("默认构造");
	}

	// 拷贝构造
	inline TBString::TBString(const TBString& str)
		: size(str.size)
		, capacity(str.size + 1)
		, data(new tchar[capacity])
	{
		memcpy(data, str.data, sizeof(tchar) * (size + 1));
		_DEBUG_ECHO_CLASS_NAME("拷贝构造")
	}

	// 字符串构造
	inline TBString::TBString(const tchar str[])
		: size(StrLen(str))
		, capacity(size+1)
		, data(new tchar[capacity])
	{
		for (size_t i = 0; i < size+1; i++)
			data[i] = str[i];
		_DEBUG_ECHO_CLASS_NAME("字符串构造");
	}
	// 字符数组构造
	inline TBString::TBString(const tchar str[], size_t n)
		: size(n)
		, capacity(n + 1)
		, data(new tchar[capacity])
	{
		for (size_t i = 0; i < size; i++)
			data[i] = str[i];
		data[n] = '\0';
		_DEBUG_ECHO_CLASS_NAME("字符串构造");
	}
	// 字符构造
	inline TBString::TBString(tchar c)
		: size(1)
		, capacity(size + 1)
		, data(new tchar[capacity])
	{
		data[0] = c;
		data[1] = '\0';
		_DEBUG_ECHO_CLASS_NAME("字符构造");
	}

	// 赋值
	inline TBString& TBString::Assign(const TBString&str)
	{
		AutoExtendCapacity(str.Size() - Size());
		size = str.Size();
		return *this;
		for (size_t i = 0; i < Size(); i++)
			data[i] = str[i];
	}
	inline TBString::~TBString()
	{
		delete[]data;
	}
	// 赋值
	inline TBString& TBString::Assign(const tchar str[])
	{
		size_t len = StrLen(str);
		AutoExtendCapacity(len - Size());
		size = len;
		return *this;
		for (size_t i = 0; i < Size(); i++)
			data[i] = str[i];
		return *this;
	}
	// 赋值
	inline TBString& TBString::Assign(tchar c)
	{
		return Assign(TBString(c));
	}
	// 追加
	inline TBString& TBString::Append(const TBString&str)
	{
		Insert(size, str);
		return *this;
	}
	// 追加
	inline TBString& TBString::Append(const tchar str[])
	{
		Insert(size, str);
		return *this;
	}
	// 追加
	inline TBString& TBString::Append(tchar c)
	{
		Insert(size, c);
		return *this;
	}
	inline TBString& TBString::Append(int n)
	{
		Insert(size, To_TBString((int)(n)));
		return *this;
	}
	// 赋值
	inline TBString& TBString::operator=(const TBString&str)
	{
		return Assign(str);
	}
	// 赋值
	inline TBString& TBString::operator=(const tchar str[])
	{
		return Assign(str);
	}
	// 赋值
	inline TBString& TBString::operator=(tchar c)
	{
		return Assign(c);
	}
	// 追加
	inline TBString& TBString::operator+=(const TBString&str)
	{
		return Append(str);
	}
	// 追加
	inline TBString& TBString::operator+=(const tchar str[])
	{
		return Append(str);
	}
	// 追加
	inline TBString& TBString::operator+=(tchar c)
	{
		return Append(c);
	}
	// 追加
	inline TBString& TBString::operator+=(int n)
	{
		Insert(size, To_TBString(n));
		return *this;
	}
	// 返回连接串
	inline TBString TBString::operator+(const TBString&str)const
	{
		return (TBString(*this).Append(str));
	}
	// 返回连接串
	inline TBString TBString::operator+(const tchar str[])const
	{
		return (TBString(*this) + To_TBString(str));
	}
	// 返回连接串
	inline TBString TBString::operator+(tchar c)const
	{
		return (TBString(*this) + To_TBString(c));
	}
	// 返回连接串
	inline TBString TBString::operator+(int n)const
	{
		return (TBString(*this) + To_TBString(n));
	}


	// 插入
	inline void TBString::Insert(size_t pos, const TBString&list)
	{
		AutoExtendCapacity(list.Len());
		memmove(data + pos + list.Len(), data + pos, (size - pos) * sizeof(tchar));
		memcpy(data + pos, list.data, list.size * sizeof(tchar));
		size += list.Len();
		data[size] = '\0';
	}
	// 插入
	inline void TBString::Insert(size_t pos, const tchar str[])
	{
		size_t str_len = StrLen(str);
		AutoExtendCapacity(str_len);
		memmove(data + pos + str_len, data + pos, (size - pos) * sizeof(tchar));
		memcpy(data + pos, str, str_len * sizeof(tchar));
		size += str_len;
		data[size] = '\0';
	}
	// 插入
	inline void TBString::Insert(size_t pos, tchar t)
	{
		AutoExtendCapacity(1);
		memmove(data + pos + 1, data + pos, (size - pos) * sizeof(tchar));
		memcpy(data + pos, &t, sizeof(tchar));
		++size;
		data[size] = '\0';
	}
	inline size_t TBString::Remove(tchar c)
	{
		size_t beg = size;
		size_t write, read;
		for (size_t i = 0; i < Size(); ++i)
		{
			if (c == data[i])
			{
				beg = i;
				break;
			}
		}
		for (write = beg, read = beg + 1; read < Size(); ++read)
		{
			if (c == data[read])
				;
			else
			{
				data[write] = data[read];
				++write;
			}
		}
		for (size_t i = write; i < Size(); ++i)
			data[i].~tchar();
		size = write;
		return size;
	}
	inline size_t TBString::Erase(size_t pos)
	{
		if (pos > Size())
			throw(TEXT("移除下标越界"));
		memcpy(data + pos, data + pos + 1, sizeof(tchar) * (Size() - pos - 1));
		--size;
		return pos;
	}
	inline size_t TBString::Erase(size_t beg, size_t end)
	{
		if (end > Size() || beg >= end)
			throw(TEXT("移除下标越界"));
		memcpy(data + beg, data + end, sizeof(tchar) * (Size() - end));
		size -= end - beg;
		return beg;
	}
	// 返回C风格字符串
	inline const tchar* TBString::C_Str() const
	{
		return data;
	}
	// 安全地访问指定元素
	inline tchar& TBString::At(size_t off)
	{
		if (off > size)
		{
			throw std::out_of_range(typeid(*this).name());
			return data[size];
		}
		else
		{
			return data[off];
		}
	}
	// 安全地访问指定元素
	inline const tchar& TBString::At(size_t off) const
	{
		if (off > size)
		{
			throw std::out_of_range(typeid(*this).name());
			return '\0';
		}
		else
		{
			return data[off];
		}
	}
	// 返回串长度
	inline size_t TBString::Len() const
	{
		return Size();
	}
	// 返回串长度
	inline size_t TBString::Size() const
	{
		return size;
	}
	// 返回容量
	inline size_t TBString::Capacity() const
	{
		return capacity;
	}
	inline tchar& TBString::operator[](size_t off)
	{
		return data[off];
	}
	inline const tchar& TBString::operator[](size_t off) const
	{
		return data[off];
	}
	inline bool TBString::AutoExtendCapacity(int append_size)
	{
		if ((int)(size + 1 + append_size) > (int)capacity)
		{
			while (size + 1 + append_size > capacity)
			{
				capacity = capacity + capacity / 2 + 1;
			}

			auto old_data = data;
			data = new tchar[capacity];
			memcpy(data, old_data, sizeof(tchar) * (size + 1));
			delete[]old_data;

			_DEBUG_ECHO_CLASS_NAME("扩充长度" << Size() << "(+" << append_size << ')');
			return true;
		}
		return false;
	}
	// 清空
	inline void TBString::Clear()
	{
		size = 0;
		data[0] = '\0';
	}
	// 判断为空
	inline bool TBString::Empty() const
	{
		return size == 0;
	}
	// 返回末尾元素
	inline tchar& TBString::Back()
	{
		return data[size - 1];
	}
	// 返回末尾元素
	inline const tchar& TBString::Back() const
	{
		return data[size - 1];
	}
	inline void TBString::PushFront(const tchar&c)
	{
		Insert(0, c);
	}
	inline void TBString::PushFront(const TBString&str)
	{
		Insert(0, str);
	}
	// 返回子串
	inline TBString TBString::SubStr(size_t off, size_t count) const
	{
		return TBString(data + off, count > Len() ? Len() : count);
	}
	inline TBString& TBString::Reverse(size_t off, size_t count)
	{
		if (count > Len())
			count = Len();
		std::reverse(data + off, data + off + count);
		return *this;
	}
	// 搜索
	inline size_t TBString::Search(const TBString& pattern, size_t beg)
	{
		for (size_t i = beg; i < Len(); ++i)
		{
			size_t ptrPat = 0;
			for (; ptrPat < pattern.Len(); ++ptrPat)
				if (data[i + ptrPat] != pattern[ptrPat])
					break;
			if (ptrPat == pattern.Len())
				return i;
		}
	}
	inline size_t TBString::ReplaceFirst(const TBString& pattern, const TBString& str)
	{
		size_t pos = Search(pattern);
		if (pos >= Len())
			return size;
		if (str.Len() == pattern.Len())	// 无须扩充
		{
			memcpy(data + pos, str.data, str.Len() * sizeof(tchar));										// 复制内容
		}
		else
		{
			if (str.Len() > pattern.Len())
				AutoExtendCapacity(str.Len() - pattern.Len());
			memcpy(data + pos + str.Len(), data + pos + pattern.Len(), (size - pos - pattern.Len() + 1) * sizeof(tchar));// 移动内存
			memcpy(data + pos, str.data, str.Len() * sizeof(tchar));										// 复制内容
			size = size + str.Len() - pattern.Len();
		}
		return pos + str.Len();
	}
	inline size_t TBString::Replace(const TBString& pattern, const TBString& str)
	{
		TBSeqList<size_t> PatternOffsetList;
		size_t pos = 0;
		while ((pos = Search(pattern, pos)) < Len())		// 查找并存储所有匹配位置
			PatternOffsetList.PushBack(pos);
		// TODOs

	}
	// 搜索
	template<typename FunT>
	inline size_t TBString::SearchIf(FunT Fun, size_t beg)
	{
		for (size_t i = beg; i < Len(); ++i)
		{
			if (Fun(data[i]))
				return i;
		}
	}

	// 添加末尾元素
	inline void TBString::PushBack(const tchar&c)
	{
		Insert(size, c);
	}
	// 添加末尾元素
	inline void TBString::PushBack(const TBString&str)
	{
		Insert(size, str);
	}
	inline void TBString::PopFront()
	{
		Erase(0);
	}
	// 移除末尾元素
	inline void TBString::PopBack()
	{
		Erase(size - 1);
	}
	inline tchar& TBString::Front()
	{
		return data[0];
	}
	inline const tchar& TBString::Front() const
	{
		return data[0];
	}
	// 转换TBString
	inline TBString To_TBString(int n)
	{
		tchar buff[_MAX_PATH];
		sprintf(buff, "%d", n);
		return TBString(buff);
	}
	// 转换TBString
	inline TBString To_TBString(tchar c)
	{
		return TBString(c);
	}
	// 转换TBString
	inline TBString To_TBString(const tchar str[])
	{
		return TBString(str);
	}
	// 转换TBString
	inline TBString To_TBString(double f)
	{
		tchar buff[_MAX_PATH];
		sprintf(buff, "%lf", f);
		return TBString(buff);
	}
	// 快速统计字符串长度
	size_t StrLen(const char* str)
	{
		using ulong=unsigned long;
		const char* char_ptr;
		const ulong* longword_ptr;
		register ulong longword;
		register ulong himagic = 0B10000000'10000000'10000000'10000000;
		register ulong lomagic = 0B00000001'00000001'00000001'00000001;
		for (char_ptr = str; ((ulong)char_ptr
							  & (sizeof(ulong) - 1)) != 0; ++char_ptr)
		{
			if (*char_ptr == '\0')
				return char_ptr - str;
		}
		longword_ptr = (ulong*)char_ptr;

		for (;;)
		{
			longword = *longword_ptr++;

			if (((longword - lomagic) & himagic) != 0)
			{
				const char* cp = (const char*)(longword_ptr - 1);
				if (cp[0] == 0)
					return cp - str;
				if (cp[1] == 0)
					return cp - str + 1;
				if (cp[2] == 0)
					return cp - str + 2;
				if (cp[3] == 0)
					return cp - str + 3;
			}
		}
	}
	size_t StrLen(const wchar_t* str)
	{
		// TODO 完成UNICODE字符长度计算函数优化
		using ulong=unsigned long;
		const wchar_t* char_ptr;
		const ulong* longword_ptr;
		register ulong longword;
		register ulong himagic = 0B10000000'10000000'10000000'10000000;
		register ulong lomagic = 0B00000001'00000001'00000001'00000001;
		for (char_ptr = str; ((ulong)char_ptr
							  & (sizeof(ulong) - 1)) != 0; ++char_ptr)
		{
			if (*char_ptr == '\0')
				return char_ptr - str;
		}
		longword_ptr = (ulong*)char_ptr;

		for (;;)
		{
			longword = *longword_ptr++;

			if (((longword - lomagic) & himagic) != 0)
			{
				const wchar_t* cp = (const wchar_t*)(longword_ptr - 1);
				if (cp[0] == 0)
					return cp - str;
				if (cp[1] == 0)
					return cp - str + 1;
			}
		}
	}
}

#endif // !THATBOY_STRING_H