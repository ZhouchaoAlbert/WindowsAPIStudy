
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

    bool Load(LPCTSTR pstrXML);    //���ز�����XML������XML�����  
    bool LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8); //����
    bool LoadFromFile(LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8); //����XML�ļ� 
    void Release(); 
    bool IsValid() const;

   void SetPreserveWhitespace(bool bPreserve = true);
   void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
   void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

   CMarkupNode GetRoot(); //��ȡXML���ĸ����

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

   CMarkupNode GetParent();  //��ȡ����� 
   CMarkupNode GetSibling(); //��ȡ��һ���ٵ��ֵܽ��
   CMarkupNode GetChild();   //��ȡ���ӽ��
   CMarkupNode GetChild(LPCTSTR pstrName);//�������ֻ�ȡ���ӽ��

   bool HasSiblings() const;
   bool HasChildren() const;//�к���
   LPCTSTR GetName() const; //��ȡ��������
   LPCTSTR GetValue() const;//��ȡ����ֵ

   bool HasAttributes();
   bool HasAttribute(LPCTSTR pstrName);//ָ������Ƿ�������� 
   int GetAttributeCount();////���е����Ը��� 
   LPCTSTR GetAttributeName(int iIndex);//����������ȡ������
   LPCTSTR GetAttributeValue(int iIndex);//����������ȡ����ֵ
   LPCTSTR GetAttributeValue(LPCTSTR pstrName);//�������ֻ�ȡ����ֵ
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



