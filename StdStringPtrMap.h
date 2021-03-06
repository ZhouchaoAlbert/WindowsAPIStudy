#pragma once
#include "DuiString.h"


struct TITEM
{
	CDuiString Key;
	LPVOID Data;
	struct TITEM* pPrev;
	struct TITEM* pNext;
};

class  CStdStringPtrMap
{
public:
	CStdStringPtrMap(int nSize = 83);
	~CStdStringPtrMap();

	void Resize(int nSize = 83);
	LPVOID Find(LPCTSTR key, bool optimize = true) const;
	bool Insert(LPCTSTR key, LPVOID pData);
	LPVOID Set(LPCTSTR key, LPVOID pData);
	bool Remove(LPCTSTR key);
	void RemoveAll();
	int GetSize() const;
	LPCTSTR GetAt(int iIndex) const;
	LPCTSTR operator[] (int nIndex) const;

protected:
	TITEM** m_aT;
	int m_nBuckets;
	int m_nCount;
};