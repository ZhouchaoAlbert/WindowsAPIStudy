#include "StdValArray.h"
#include <windows.h>

CStdValArray::CStdValArray(int iElementSize, int iPreallocSize /*= 0*/) :
m_pVoid(NULL),
m_nCount(0),
m_iElementSize(iElementSize),
m_nAllocated(iPreallocSize)
{
	//ASSERT(iElementSize > 0);
	//ASSERT(iPreallocSize >= 0);
	if (iPreallocSize > 0)
		m_pVoid = static_cast<LPBYTE>(malloc(iPreallocSize * m_iElementSize));
}

CStdValArray::~CStdValArray()
{
	if (m_pVoid != NULL) free(m_pVoid);
}

void CStdValArray::Empty()
{
	m_nCount = 0;  // NOTE: We keep the memory in place
}

bool CStdValArray::IsEmpty() const
{
	return m_nCount == 0;
}

bool CStdValArray::Add(LPCVOID pData)
{
	if (++m_nCount >= m_nAllocated) {
		int nAllocated = m_nAllocated * 2;
		if (nAllocated == 0) nAllocated = 11;
		LPBYTE pVoid = static_cast<LPBYTE>(realloc(m_pVoid, nAllocated * m_iElementSize));
		if (pVoid != NULL) {
			m_nAllocated = nAllocated;
			m_pVoid = pVoid;
		}
		else {
			--m_nCount;
			return false;
		}
	}
	::CopyMemory(m_pVoid + ((m_nCount - 1) * m_iElementSize), pData, m_iElementSize);
	return true;
}

bool CStdValArray::Remove(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_nCount) return false;
	if (iIndex < --m_nCount) ::CopyMemory(m_pVoid + (iIndex * m_iElementSize), m_pVoid + ((iIndex + 1) * m_iElementSize), (m_nCount - iIndex) * m_iElementSize);
	return true;
}

int CStdValArray::GetSize() const
{
	return m_nCount;
}

LPVOID CStdValArray::GetData()
{
	return static_cast<LPVOID>(m_pVoid);
}

LPVOID CStdValArray::GetAt(int iIndex) const
{
	if (iIndex < 0 || iIndex >= m_nCount) return NULL;
	return m_pVoid + (iIndex * m_iElementSize);
}

LPVOID CStdValArray::operator[] (int iIndex) const
{
	//ASSERT(iIndex >= 0 && iIndex < m_nCount);
	return m_pVoid + (iIndex * m_iElementSize);
}