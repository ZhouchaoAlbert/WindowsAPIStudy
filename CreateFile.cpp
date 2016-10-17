#include "CreateFile.h"
#include <windows.h>

CString File::OpenExitFile(CString strFilePath)
{
   //打开已存在的文件
	HANDLE hFile = ::CreateFileW(strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return _T("Open File Error");
	}
	DWORD dwSize = ::GetFileSize(hFile, NULL);
	if (0 == dwSize)
	{
		return _T("Open File is empty");
	}

	if (dwSize > 4096 * 1024)// 4M
	{
		return _T("Open File too large");
	}

	DWORD dwRead = 0;
	UINT8* pByte = new UINT8[dwSize];
	if (NULL == pByte)
	{
		return _T("");
	}
	::ReadFile(hFile, pByte, dwSize, &dwRead, NULL);
	::CloseHandle(hFile);

	//
	if (dwSize >= 3 && pByte[0] == 0xEF && pByte[1] == 0xBB && pByte[2] == 0xBF)
	{
		pByte += 3; dwSize -= 3;  //UTF8
	}
	else
	{

	}
	DWORD nWide = ::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pByte, dwSize, NULL, 0);

	LPTSTR pstrXML = static_cast<LPTSTR>(malloc((nWide + 1)*sizeof(TCHAR)));
	::MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pByte, dwSize, pstrXML, nWide);
	pstrXML[nWide] = _T('\0');

	CString strXML;
	strXML = pstrXML;

	
	delete[](pByte - 3);



	free(pstrXML);
	return strXML;


}