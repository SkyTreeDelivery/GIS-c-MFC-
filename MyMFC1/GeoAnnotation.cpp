#include "stdafx.h"
#include "GeoAnnotation.h"


CGeoAnnotation::CGeoAnnotation(void)
{
}


CGeoAnnotation::~CGeoAnnotation(void)
{
}

void CGeoAnnotation::draw(CDCInfo* info){	
	//��������
	CDC* pDC = info->pDC;
	CFont font;
	if(!font.CreatePointFont(100,_T("����"),pDC)){
		AfxMessageBox(_T("�����������"));
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&font);
	//��������
	pDC->TextOutW(this->x,this->y,this->anno);
}

void CGeoAnnotation::project(CMapProjection* projection){
	CPoint* pt = &getLocation();
	float x,y;
	projection->getXY(pt->x*1.0/MULTI,pt->y*1.0/MULTI,&x,&y);
	proPt = CPoint((int)x,(int)y);
}
