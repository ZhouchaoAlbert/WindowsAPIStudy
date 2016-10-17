#pragma once
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
using namespace ATL;

#include "CreateFile.h"
#include "FriendUnitTest.h"
#include "StdPtrArray.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{


	

 	A a(10);
 	B b;
 	b.print(a);

	CStdPtrArray m_p;
	m_p.Add(&a);
	m_p.Add(&b);

	CString strFilePath = _T("C:\\Users\\Administrator\\Desktop\\MiniQQ\\Output\\Resource\\xml\\LoginFrame.xml");
	CString 	str = File::OpenExitFile(strFilePath);
	

	str = ::CharNext(str);


	
	return 0;
}