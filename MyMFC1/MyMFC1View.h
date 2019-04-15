
// MyMFC1View.h : CMyMFC1View ��Ľӿ�
//

#pragma once

#include "stdafx.h"
#include "DCInfo.h"
#include "Excel.h"
#include "GeoObject.h"
#include "GeoPoint.h"
#include "GeoPolygon.h"
#include "GeoPolyline.h"
#include "GeoAnnotation.h"
#include "GeoLayer.h"
#include "GeoMap.h"

class CMyMFC1View : public CView
{
protected: // �������л�����
	CMyMFC1View();
	DECLARE_DYNCREATE(CMyMFC1View)

// ����
public:
	CMyMFC1Doc* GetDocument() const;

// ����
public:
	CGeoMap* map;
	layerPropotry* pros;
	CPoint downPoint;

	CPoint upPoint;
	CRect rect;
	boolean isPressed;
	int status;
	CDCInfo* info;
	CDC* MemDC;//���ȶ���һ����ʾ�豸����
	CBitmap MemBitmap;//����һ��λͼ����
	CPoint deltaAll;
	void CMyMFC1View::readWuhanData(FILE* fp);
	void CMyMFC1View::readChinaData(FILE* fp);
	void CMyMFC1View::readChinaRealData(FILE* fp);
	void CMyMFC1View::readColorFile(FILE* fp);
	void CMyMFC1View::addProsData();
	void CMyMFC1View::readExcelData(char* pathChar);
	void CMyMFC1View::readFloodFillData(FILE* fp);
	rgb CMyMFC1View::convertColor(int color);
	void CMyMFC1View::readClipData(FILE* fp);
	void CMyMFC1View::bufferedDraw(CDC* pDC);
	void CMyMFC1View::openNewMapReflash();
	CPoint CMyMFC1View::ProDelta(CDC* pDC, CPoint delta);
	void CMyMFC1View::readBLData(FILE* fp);


// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMyMFC1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonZoomin();
	afx_msg void OnButtonAll();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnButtonTranslation();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // MyMFC1View.cpp �еĵ��԰汾
inline CMyMFC1Doc* CMyMFC1View::GetDocument() const
   { return reinterpret_cast<CMyMFC1Doc*>(m_pDocument); }
#endif

