#include "stdafx.h"
#include "GeoAnnotation.h"


CGeoAnnotation::CGeoAnnotation(void)
{
}


CGeoAnnotation::~CGeoAnnotation(void)
{
}

void CGeoAnnotation::draw(CDCInfo* info){	
	//设置字体
	CDC* pDC = info->pDC;
	CFont font;
	if(!font.CreatePointFont(100,_T("隶书"),pDC)){
		AfxMessageBox(_T("设置字体错误"));
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&font);
	//绘制字体
	pDC->TextOutW(this->x,this->y,this->anno);
}

void CGeoAnnotation::project(CMapProjection* projection){
	CPoint* pt = &getLocation();
	float x,y;
	projection->getXY(pt->x*1.0/MULTI,pt->y*1.0/MULTI,&x,&y);
	proPt = CPoint((int)x,(int)y);
}
