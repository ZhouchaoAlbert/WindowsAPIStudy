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
	CDuiString(LPCTSTR lpsz, int nLen = -1); //����Ϊ-1�ɳ����Լ��жϳ���
	~CDuiString();

	void Empty();		   //����ַ���
	int GetLength() const; //��ȡ�ַ�������
	bool IsEmpty() const;  //�ַ����Ƿ�Ϊ�մ�
	TCHAR GetAt(int nIndex) const;  //��ȡָ��λ�ô����ַ�
	void Append(LPCTSTR pstr);      //�ַ���׷�Ӳ���
	void Assign(LPCTSTR pstr, int nLength = -1); //�����ڴ渳ֵ
	LPCTSTR GetData() const;// ��ȡ�ַ���ָ��

	void SetAt(int nIndex, TCHAR ch);//��ָ�������������ַ�
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

	int Compare(LPCTSTR pstr) const; // �ַ����Ƚ�
	int CompareNoCase(LPCTSTR pstr) const;//�ַ������Դ�Сд�Ƚ�

	void MakeUpper();//�ַ���ת��Ϊ��xie
	void MakeLower(); //�ַ���ת��ΪСд

	CDuiString Left(int nLength) const;//����߽�ȡָ�����ȵ��Ӵ�
	CDuiString Mid(int iPos, int nLength = -1) const;// ��ȡ�м��ַ���
	CDuiString Right(int nLength) const;//���ҿ�ʼ��ȡָ�����ȵ��ַ���

	int Find(TCHAR ch, int iPos = 0) const;//��ָ��λ�ÿ�ʼѰ��ƥ���ַ���λ��
	int Find(LPCTSTR pstr, int iPos = 0) const;//��ָ��λ�ÿ�ʼѰ��ƥ���ַ�����λ��
	int ReverseFind(TCHAR ch) const; // �����ѯ�ַ�λ��
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo); // ��ƥ����ַ��Ӵ���ָ���ַ����滻

	int __cdecl Format(LPCTSTR pstrFormat, ...);  //�63λ���ַ�����ʽ��
	int __cdecl Format(LPCTSTR pstrFormat, va_list Args);//һ�θ�ʽ��1024���ȵ��ַ�����ʽ��
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;  // �ַ�ָ��
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];//�ַ�������
};
