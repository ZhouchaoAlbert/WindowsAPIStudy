#pragma once
#include<atlstr.h>
using namespace std;

/*
��A�����friend class B;  ʹ��B����Է���A�������protected��private�ĳ�Ա�������Ա����
��ˣ�������B����ʹ��a.x������A���˽�г�Աint x;  ���û����䣬��δ�����벻���ġ�
��ע��һ�㣬��A������������䣬ֻ����B���ڲ�����A��ı�����˽�г�Ա����֮A�಻�ܷ���B�ౣ����˽�г�Ա
*/

/*
1.��Ԫ����
2.��Ԫ��
*/
class A;
 class A
 {
 	friend class B;	
	 //BΪ��Ԫ��
	 A()
	 {
	 }
 public:
 	//friend void FunctinB(A aa); //��Ԫ����
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
