
// MyMFC1.h : MyMFC1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyMFC1App:
// �йش����ʵ�֣������ MyMFC1.cpp
//

class CMyMFC1App : public CWinAppEx
{
public:
	CMyMFC1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyMFC1App theApp;
