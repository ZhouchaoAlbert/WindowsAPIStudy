#pragma once
#include<atlstr.h>
using namespace std;

/*
在A里面加friend class B;  使得B类可以访问A类里面的protected和private的成员函数或成员变量
因此，可以在B里面使用a.x来访问A类的私有成员int x;  如果没有这句，这段代码编译不过的。
但注意一点，在A里面声明了这句，只能让B类内部访问A类的保护或私有成员，反之A类不能访问B类保护或私有成员
*/

/*
1.友元函数
2.友元类
*/
class A;
 class A
 {
 	friend class B;	
	 //B为友元类
	 A()
	 {
	 }
 public:
 	//friend void FunctinB(A aa); //友元函数
 public:
 	A(int a)
 	{ 
 		x = a; 
 	}
 private:
 	int x;
 };
 
//  void FunctinB(A aa)
//  {
//  	aa.x--;
//   	CString str;
//   	str.Format(_T("Functin:%d"), aa.x);
//   	MessageBox(NULL, str, str, MB_OK);
//  }

 class B
 {
 public:
 	void print(A a)
 	{
 		a.x--;
 		CString str;
 		str.Format(_T("print:%d"), a.x);
 		MessageBox(NULL, str, str, MB_OK);
 	}
 };
