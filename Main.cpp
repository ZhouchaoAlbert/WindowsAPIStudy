#pragma once
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
using namespace ATL;

#include "CreateFile.h"

/*
��A�����friend class B;  ʹ��B����Է���A�������protected��private�ĳ�Ա�������Ա����
��ˣ�������B����ʹ��a.x������A���˽�г�Աint x;  ���û����䣬��δ�����벻���ġ�
��ע��һ�㣬��A������������䣬ֻ����B���ڲ�����A��ı�����˽�г�Ա����֮A�಻�ܷ���B�ౣ����˽�г�Ա
*/

/*
1.��Ԫ����
2.��Ԫ��
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