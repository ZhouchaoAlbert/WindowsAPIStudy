#pragma once
typedef void* LPVOID;
//指针数组
//其实类指针数组就是指向类的指针的一个指针，是二级指针
class CStdPtrArray
{
public:
	CStdPtrArray(int iPreallocSize = 0);
	CStdPtrArray(const CStdPtrArray& src);
	~CStdPtrArray();

	void Empty();  //清空
	void Resize(int iSize);
	bool IsEmpty() const;
	int Find(LPVOID iIndex) const;
	bool Add(LPVOID pData);
	bool SetAt(int iIndex, LPVOID pData);
	bool InsertAt(int iIndex, LPVOID pData);
	bool Remove(int iIndex);
	int GetSize() const;
	LPVOID* GetData();

	LPVOID GetAt(int iIndex) const;
	LPVOID operator[] (int nIndex) const;

protected:
	LPVOID* m_ppVoid;
	int m_nCount;      //个数
	int m_nAllocated;  //已经申请的内存



};


