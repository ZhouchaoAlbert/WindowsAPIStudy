#pragma once
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
using namespace ATL;

#include "CreateFile.h"

/*
在A里面加friend class B;  使得B类可以访问A类里面的protected和private的成员函数或成员变量
因此，可以在B里面使用a.x来访问A类的私有成员int x;  如果没有这句，这段代码编译不过的。
但注意一点，在A里面声明了这句，只能让B类内部访问A类的保护或私有成员，反之A类不能访问B类保护或私有成员
*/

/*
1.友元函数
2.友元类
*/
class A
{
	friend class B;
public:
	A(int a){ x = a; }
private:
	int x;
	
};
class B
{
public:
	void print(A a)
	{
		a.x--;
		CString str;
		str.Format(_T("%d"), a.x);
		MessageBox(NULL, str, str, MB_OK);
	}
};



int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	A a(10); B b;
	b.print(a);

	CString strFilePath = _T("C:\\Users\\Administrator\\Desktop\\MiniQQ\\Output\\Resource\\xml\\LoginFrame.xml");
	CString 	str = File::OpenExitFile(strFilePath);
	

		str = ::CharNext(str);

		str = ::CharNext(str);
	
	return 0;
}