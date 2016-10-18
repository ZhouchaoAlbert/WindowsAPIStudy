#pragma once
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef unsigned char  *LPBYTE;
class  CStdValArray
{
public:
	CStdValArray(int iElementSize, int iPreallocSize = 0);
	~CStdValArray();

	void Empty();
	bool IsEmpty() const;
	bool Add(LPCVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPBYTE m_pVoid;
	int m_iElementSize;
	int m_nCount;
	int m_nAllocated;
};