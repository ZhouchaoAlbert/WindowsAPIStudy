#pragma once
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
using namespace ATL;

#include "CreateFile.h"
#include "FriendUnitTest.h"
#include "StdPtrArray.h"
#include "DuiString.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	CDuiString str2(_T("fdsfdgdsg  dgfdgfdgfg  rgrehrthrthtyjyjtyykykuyktyjrthwregegregrhrthrtghergqegqegrg"));

	const char* p = "dsfsfs";
	str2 = p;
	str2.Append(_T("55555"));


 	A a(10);
	A c(9);
	A d(8);
 	B b;
 	b.print(a);

	CStdPtrArray m_p;
	m_p.Add(&a);
	m_p.Add(&c);
	m_p.InsertAt(1, &d);


	CString strFilePath = _T("C:\\Users\\Administrator\\Desktop\\MiniQQ\\Output\\Resource\\xml\\LoginFrame.xml");
	CString 	str = File::OpenExitFile(strFilePath);
	

	str = ::CharNext(str);


	
	return 0;
}