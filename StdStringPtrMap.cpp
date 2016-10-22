#include "StdStringPtrMap.h"

static UINT HashKey(LPCTSTR Key)
{
	UINT i = 0;
	SIZE_T len = _tcslen(Key);
	while (len-- > 0)
		i = (i << 5) + i + Key[len];
	return i;
}

static UINT HashKey(const CDuiString& Key)
{
	return HashKey((LPCTSTR)Key);
};

CStdStringPtrMap::CStdStringPtrMap(int nSize) : m_nCount(0)
{
	if (nSize < 16) 
		nSize = 16;
	m_nBuckets = nSize;
	m_aT = new TITEM*[nSize];
	memset(m_aT, 0, nSize * sizeof(TITEM*));
}

CStdStringPtrMap::~CStdStringPtrMap()
{
	if (m_aT) {
		int len = m_nBuckets;
		while (len--) {
			TITEM* pItem = m_aT[len];
			while (pItem) {
				TITEM* pKill = pItem;
				pItem = pItem->pNext;
				delete pKill;
			}
		}
		delete[] m_aT;
		m_aT = NULL;
	}
}

void CStdStringPtrMap::RemoveAll()
{
	this->Resize(m_nBuckets);
}

void CStdStringPtrMap::Resize(int nSize)
{
	if (m_aT) 
	{
		int len = m_nBuckets;
		while (len--) 
		{
			TITEM* pItem = m_aT[len];
			while (pItem) {
				TITEM* pKill = pItem;
				pItem = pItem->pNext;
				delete pKill;
			}
		}
		delete[] m_aT;
		m_aT = NULL;
	}

	if (nSize < 0) nSize = 0;
	if (nSize > 0) 
	{
		m_aT = new TITEM*[nSize];
		memset(m_aT, 0, nSize * sizeof(TITEM*));
	}
	m_nBuckets = nSize;
	m_nCount = 0;
}

LPVOID CStdStringPtrMap::Find(LPCTSTR key, bool optimize) const
{
	if (m_nBuckets == 0 || GetSize() == 0) return NULL;

	UINT slot = HashKey(key) % m_nBuckets;
	for (TITEM* pItem = m_aT[slot]; pItem; pItem = pItem->pNext) {
		if (pItem->Key == key) {
			if (optimize && pItem != m_aT[slot]) 
			{
				if (pItem->pNext) 
				{
					pItem->pNext->pPrev = pItem->pPrev;
				}
				pItem->pPrev->pNext = pItem->pNext;
				pItem->pPrev = NULL;
				pItem->pNext = m_aT[slot];
				pItem->pNext->pPrev = pItem;
				//将item移动至链条头部
				m_aT[slot] = pItem;
			}
			return pItem->Data;
		}
	}

	return NULL;
}

bool CStdStringPtrMap::Insert(LPCTSTR key, LPVOID pData)
{
	if (m_nBuckets == 0) return false;
	if (Find(key)) return false;

	// Add first in bucket
	UINT slot = HashKey(key) % m_nBuckets;
	TITEM* pItem = new TITEM;
	pItem->Key = key;
	pItem->Data = pData;
	pItem->pPrev = NULL;
	pItem->pNext = m_aT[slot];
	if (pItem->pNext)
		pItem->pNext->pPrev = pItem;
	m_aT[slot] = pItem;
	m_nCount++;
	return true;
}

LPVOID CStdStringPtrMap::Set(LPCTSTR key, LPVOID pData)
{
	if (m_nBuckets == 0) return pData;

	if (GetSize() > 0) 
	{
		UINT slot = HashKey(key) % m_nBuckets;
		// Modify existing item
		for (TITEM* pItem = m_aT[slot]; pItem; pItem = pItem->pNext) 
		{
			if (pItem->Key == key) {
				LPVOID pOldData = pItem->Data;
				pItem->Data = pData;
				return pOldData;
			}
		}
	}

	Insert(key, pData);
	return NULL;
}

bool CStdStringPtrMap::Remove(LPCTSTR key)
{
	if (m_nBuckets == 0 || GetSize() == 0) return false;

	UINT slot = HashKey(key) % m_nBuckets;
	TITEM** ppItem = &m_aT[slot];
	while (*ppItem) 
	{
		if ((*ppItem)->Key == key) {
			TITEM* pKill = *ppItem;
			*ppItem = (*ppItem)->pNext;
			if (*ppItem)
				(*ppItem)->pPrev = pKill->pPrev;
			delete pKill;
			m_nCount--;
			return true;
		}
		ppItem = &((*ppItem)->pNext);
	}

	return false;
}

int CStdStringPtrMap::GetSize() const
{
#if 0//def _DEBUG
	int nCount = 0;
	int len = m_nBuckets;
	while (len--) {
		for (const TITEM* pItem = m_aT[len]; pItem; pItem = pItem->pNext) nCount++;
	}
	ASSERT(m_nCount == nCount);
#endif
	return m_nCount;
}

LPCTSTR CStdStringPtrMap::GetAt(int iIndex) const
{
	if (m_nBuckets == 0 || GetSize() == 0) return false;

	int pos = 0;
	int len = m_nBuckets;
	while (len--) {
		for (TITEM* pItem = m_aT[len]; pItem; pItem = pItem->pNext) {
			if (pos++ == iIndex) {
				return pItem->Key.GetData();
			}
		}
	}

	return NULL;
}

LPCTSTR CStdStringPtrMap::operator[] (int nIndex) const
{
	return GetAt(nIndex);
}

