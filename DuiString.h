#pragma once

#include <tchar.h>
#include <windows.h>
#include "ole2.h"
class  CDuiString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	CDuiString();
	CDuiString(const TCHAR ch);
	CDuiString(const CDuiString& src);
	CDuiString(LPCTSTR lpsz, int nLen = -1); //长度为-1由程序自己判断长度
	~CDuiString();

	void Empty();		   //清空字符串
	int GetLength() const; //获取字符串长度
	bool IsEmpty() const;  //字符串是否为空串
	TCHAR GetAt(int nIndex) const;  //获取指定位置处的字符
	void Append(LPCTSTR pstr);      //字符串追加操作
	void Assign(LPCTSTR pstr, int nLength = -1); //分配内存赋值
	LPCTSTR GetData() const;// 获取字符串指针

	void SetAt(int nIndex, TCHAR ch);//在指定索引处设置字符
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const CDuiString& operator=(const CDuiString& src);
	const CDuiString& operator=(const TCHAR ch);
	const CDuiString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
	const CDuiString& CDuiString::operator=(LPCSTR lpStr);
	const CDuiString& CDuiString::operator+=(LPCSTR lpStr);
#else
	const CDuiString& CDuiString::operator=(LPCWSTR lpwStr);
	const CDuiString& CDuiString::operator+=(LPCWSTR lpwStr);
#endif
	CDuiString operator+(const CDuiString& src) const;
	CDuiString operator+(LPCTSTR pstr) const;
	const CDuiString& operator+=(const CDuiString& src);
	const CDuiString& operator+=(LPCTSTR pstr);
	const CDuiString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const; // 字符串比较
	int CompareNoCase(LPCTSTR pstr) const;//字符串忽略大小写比较

	void MakeUpper();//字符串转换为大xie
	void MakeLower(); //字符串转换为小写

	CDuiString Left(int nLength) const;//从左边截取指定长度的子串
	CDuiString Mid(int iPos, int nLength = -1) const;// 截取中间字符串
	CDuiString Right(int nLength) const;//从右开始截取指定长度的字符串

	int Find(TCHAR ch, int iPos = 0) const;//从指定位置开始寻找匹配字符的位置
	int Find(LPCTSTR pstr, int iPos = 0) const;//重指定位置开始寻找匹配字符串的位置
	int ReverseFind(TCHAR ch) const; // 反向查询字符位置
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo); // 将匹配的字符子串用指定字符串替换

	int __cdecl Format(LPCTSTR pstrFormat, ...);  //最长63位的字符串格式化
	int __cdecl Format(LPCTSTR pstrFormat, va_list Args);//一次格式化1024长度的字符串格式化
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;  // 字符指针
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];//字符缓冲区
};
