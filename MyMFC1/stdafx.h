
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


//�������״̬����
#define ZOOMIN 10000
#define ALL 10001
#define MOVE 10002
#define NO_ZOOMIN 10003
#define TRANSLATION 10004
#define MULTI 1000000
#define LEFT 1000
#define RIGHT 1001
#define TOP 1002
#define BOTTOM 1003


struct rgb{
	int r;
	int g;
	int b;
};

struct CPt{
	CPoint cross; 
	int t;
};

struct layerPropotry{
	CString* layerName;
	int hasPolyline;
	double lineWidth;
	rgb polylineColor;
	int hasPolygon;
	rgb polygonColor;
};

#include "DCInfo.h"
#include "Excel.h"
#include "GeoLayer.h"
#include "GeoObject.h"
#include "GeoPoint.h"
#include "GeoPolygon.h"
#include "GeoPolyline.h"
#include "GeoAnnotation.h"
#include "GeoMap.h"
#include "MapProjection.h"
#include "MapProjectionMercator.h"
/*#include "MapProjection.h"
#include "MapProjectionMercator.h"*/


