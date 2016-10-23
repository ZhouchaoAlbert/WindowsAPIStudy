
#pragma once
#include "BaseDefine.h"

enum
{
    XMLFILE_ENCODING_UTF8 = 0,
    XMLFILE_ENCODING_UNICODE = 1,
    XMLFILE_ENCODING_ASNI = 2,
};

class CMarkup;
class CMarkupNode;


class CMarkup
{
friend class CMarkupNode;
public:
   CMarkup(LPCTSTR pstrXML = NULL);
   ~CMarkup();

    bool Load(LPCTSTR pstrXML);    //加载并分析XML，构建XML结点树  
    bool LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8); //解析
    bool LoadFromFile(LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8); //加载XML文件 
    void Release(); 
    bool IsValid() const;

   void SetPreserveWhitespace(bool bPreserve = true);
   void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
   void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

   CMarkupNode GetRoot(); //获取XML树的根结点

private:
   typedef struct tagXMLELEMENT
   {
      ULONG iStart;
      ULONG iChild;
      ULONG iNext;
      ULONG iParent;
      ULONG iData;
   } XMLELEMENT;
   
   LPTSTR m_pstrXML;
   XMLELEMENT* m_pElements;
   ULONG m_nElements;
   ULONG m_nReservedElements;
   TCHAR m_szErrorMsg[100];
   TCHAR m_szErrorXML[50];
   bool m_bPreserveWhitespace;

private:
   bool _Parse();
   bool _Parse(LPTSTR& pstrText, ULONG iParent);
   XMLELEMENT* _ReserveElement();
   inline void _SkipWhitespace(LPTSTR& pstr) const;
   inline void _SkipWhitespace(LPCTSTR& pstr) const;
   inline void _SkipIdentifier(LPTSTR& pstr) const;
   inline void _SkipIdentifier(LPCTSTR& pstr) const;
   bool _ParseData(LPTSTR& pstrText, LPTSTR& pstrData, char cEnd);
   void _ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);
   bool _ParseAttributes(LPTSTR& pstrText);
   bool _Failed(LPCTSTR pstrError, LPCTSTR pstrLocation = NULL);
};


class CMarkupNode
{
    friend class CMarkup;
private:
   CMarkupNode();
   CMarkupNode(CMarkup* pOwner, int iPos);

public:
   bool IsValid() const;

   CMarkupNode GetParent();  //获取父结点 
   CMarkupNode GetSibling(); //获取下一紧临的兄弟结点
   CMarkupNode GetChild();   //获取孩子结点
   CMarkupNode GetChild(LPCTSTR pstrName);//根据名字获取孩子结点

   bool HasSiblings() const;
   bool HasChildren() const;//有孩子
   LPCTSTR GetName() const; //获取属性名字
   LPCTSTR GetValue() const;//获取属性值

   bool HasAttributes();
   bool HasAttribute(LPCTSTR pstrName);//指定结点是否具有属性 
   int GetAttributeCount();////具有的属性个数 
   LPCTSTR GetAttributeName(int iIndex);//根据索引获取属性名
   LPCTSTR GetAttributeValue(int iIndex);//根据索引获取属性值
   LPCTSTR GetAttributeValue(LPCTSTR pstrName);//根据名字获取属性值
   bool GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax);
   bool GetAttributeValue(LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax); 

private:
   void _MapAttributes();

    enum { MAX_XML_ATTRIBUTES = 64 };

   typedef struct
   {
      ULONG iName;
      ULONG iValue;
   } XMLATTRIBUTE;

   int m_iPos;
   int m_nAttributes;
   XMLATTRIBUTE m_aAttributes[MAX_XML_ATTRIBUTES];
   CMarkup* m_pOwner;
};



