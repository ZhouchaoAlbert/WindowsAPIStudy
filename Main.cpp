#pragma once
#include <Windows.h>
#include <tchar.h>
#include <atlstr.h>
using namespace ATL;

#include "CreateFile.h"
#include "FriendUnitTest.h"
#include "StdPtrArray.h"
#include "DuiString.h"
#include "StdStringPtrMap.h"
#include "Delegate.h"
#include "Singleton.h"
#include "UIMarkup.h"


bool FunctionTest(void*)
{
	return true;
}

class ClsA
{
public:
	CEventSource EventA;

	void GetList()
	{
		DoA();
	}
	void DoA() 
	{
		EventA(NULL);
	}
};

class ClsB
{
public:
	bool FunctionTest(void*)
	{
		return true;
	}


};



enum enumReg
{
	REG_AA,
	REG_BB,
	REG_CC,
};

class AA
{
public:
	CEventSource eA;
	CEventSource eB;
	CEventSource eC;



	void DoTask(enumReg eReg)
	{
		switch (eReg)
		{
		case REG_AA:
			DoA(); break;
		case REG_BB:
			DoB(); break;
		case REG_CC:
			DoC(); break;
		default:
			break;
		}
	}
	void DoA()
	{
		eA(NULL);
	}
	void DoB()
	{
		eB(NULL);
	}
	void DoC()
	{
		eC(NULL);
	}

};





template <class O, class T>
void RegFuction(enumReg eReg,O* p, bool (T::* pFn)(void*))
{

		switch (eReg)
		{
		case REG_AA:
			Singleton<AA>::Instance().eA += MakeDelegate(p, pFn); break;
		case REG_BB:
			Singleton<AA>::Instance().eB += MakeDelegate(p, pFn); break;
		case REG_CC:
			Singleton<AA>::Instance().eC += MakeDelegate(p, pFn); break;
		default:
			break;
		}
	
}

void DoTask(enumReg eReg)
{
	Singleton<AA>::Instance().DoTask(eReg);
}

#define REGISTER_XTRAITS_HANDLER(eReg, p, pFn)  RegFuction(eReg,p, pFn);


class BB
{
public:

	BB()
	{
		REGISTER_XTRAITS_HANDLER(REG_AA, this, &BB::FA);
		REGISTER_XTRAITS_HANDLER(REG_BB, this, &BB::FB);
	}

	AA m_a;
	void Init()
	{
		m_a.eA += MakeDelegate(this, &BB::FA);
		m_a.eB += MakeDelegate(this, &BB::FB);
		m_a.eC += MakeDelegate(this, &BB::FC);
	}

	bool FA(void *)
	{
		return true;
	}
	bool FB(void *)
	{
		return true;
	}
	bool FC(void *)
	{
		return true;
	}
};

class CC
{
public:
	CC()
	{
		REGISTER_XTRAITS_HANDLER(REG_AA, this, &CC::FA);
	}
	AA m_a;
	void Init()
	{
		m_a.eA += MakeDelegate(this, &CC::FA);
		m_a.eB += MakeDelegate(this, &CC::FB);
		m_a.eC += MakeDelegate(this, &CC::FC);
	}

	bool FA(void *)
	{
		return true;
	}
	bool FB(void *)
	{
		return true;
	}
	bool FC(void *)
	{
		return true;
	}
};

void Parse(CMarkupNode* pRoot)
{
	for (CMarkupNode node = pRoot->GetChild(); node.IsValid(); node = node.GetSibling())
	{
		LPCTSTR pstrClass = node.GetName();
		// Add children
		if (node.HasChildren())
		{
			Parse(&node);
		}

		// Process attributes
		if (node.HasAttributes())
		{
			// Set ordinary attributes
			int nAttributes = node.GetAttributeCount();
			for (int i = 0; i < nAttributes; i++)
			{
				LPCTSTR pstrName  = node.GetAttributeName(i);
				LPCTSTR pstrValue = node.GetAttributeValue(i);
			}
		}
	}

}
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UINT32 I = sizeof(ULONG);
	CString strFilePath;
	strFilePath = _T("C:\\Users\\Administrator\\Desktop\\MiniQQ\\Output\\Resource\\xml\\LoginFrame.xml");

	CMarkup m_xml;
	m_xml.LoadFromFile(strFilePath);

	CMarkupNode root = m_xml.GetRoot();
	
	Parse(&root);
	

	//CDelegateStatic th(FunctionTest);	
	//th(nullptr);
// 	ClsA a;
// 	ClsB b;
// 
// 	a.EventA += MakeDelegate(&FunctionTest);
// 	a.EventA += MakeDelegate(&b, &ClsB::FunctionTest);
// 	a.GetList();

	BB n;
	CC m;
	DoTask(REG_AA);
	DoTask(REG_BB);

	return 0;
	BB bb;
	bb.Init();
	
	bb.m_a.DoB();

	bb.m_a.DoA();
	return 0;
#if 0
	CDuiString str2(_T("fdsfdgdsg  dgfdgfdgfg  rgrehrthrthtyjyjtyykykuyktyjrthwregegregrhrthrtghergqegqegrg"));

	const char* p = "dsfsfs";
	//str2 = p;
	str2.Append(_T("55555"));


 	A a(10);
	A c(9);

	CStdStringPtrMap mm;
	mm.Insert(_T("deefw"), &a);
	mm.Insert(_T("deefw"), &c);
	A* vz = (A*)mm.Find(_T("deefw"));

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


#endif	
	return 0;
}