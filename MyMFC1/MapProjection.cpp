#include "stdafx.h"
#include "MapProjection.h"
#include "math.h"


CMapProjection::CMapProjection()
{
	a = 6378137.0;
	ae = 1/198.257223565;
	b = a*(1-ae);
	e1 = sqrt(1-(b*b)/(a*a));
	e2 = sqrt((e1*e1)/(1-e1*e1));
	B0 = 0;
	L0 = 0;
	N = ((a*a)/b)/sqrt(1+e2*e2*cos(B0)*cos(B0));
	K = N * cos(B0);
}


CMapProjection::~CMapProjection(void)
{
}

//绘制方里网
void CMapProjection::draw(CDCInfo* info ){
	CDC* pDC = info->pDC; 
	CFont font;
	if(!font.CreatePointFont(100,_T("隶书"),pDC)){
		AfxMessageBox(_T("设置字体错误"));
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(&font);
	CMapProjection* projection = info->map->getProjection();
	CRect winRect = info->clientRect_real;
	CRect rect = info->map->getRect();
	int deltaDegree = 5;
	//逻辑坐标的经纬度范围
	float left = rect.left*1.0/MULTI;
	float right = rect.right*1.0/MULTI;
	float top = rect.top*1.0/MULTI;
	float bottom = rect.bottom*1.0/MULTI;
	int xn = ((int)right)/5 - ((int)left)/5;
	int yn = ((int)top)/5 - ((int)bottom)/5;
	int x0 = ((int)left)/5;
	int y0 = ((int)bottom)/5;
	//绘制纬线
	for(int i = 0; i < yn +2; i++ ){
		float y = (y0 + i) * deltaDegree;
		if(y < bottom) y = bottom;
		if(y > top) y = top;
		for(int j = 0; j < xn +2 ;j++){
			float x = (x0 + j) * deltaDegree;
			if(x < left) x = left;
			if(x > right) x= right;
			float xx,yy;
			projection->getXY(x,y,&xx,&yy);
			if(j == 0){
				pDC->MoveTo(CPoint((int)xx,(int)yy));
			}else{
				pDC->LineTo(CPoint((int)xx,(int)yy));
			}
			if(j == 0){
				//纵轴坐标的显示
				if( i == 0 ) projection->getXY(x,y+1,&xx,&yy);//第一行向上平移段距离
				CString infoStr;
				infoStr.Format(_T("%d"),(int)y);
				pDC->TextOutW(xx,yy,infoStr);
			}
		}/*
		if(y >= bottom && y <= top){
			CString infoStr;
			float xx,yy;
			projection->getXY(left,y,&xx,&yy);
			infoStr.Format(_T("%d"),(int)y);
			pDC->TextOutW(winRect.left,yy,infoStr);
		}
		*/
	}
	//方里网经线的绘制
	for(int i = 0; i < xn +2; i++ ){
		float x = (x0 + i) * deltaDegree;
		if(x < left) x = left;
		if(x > right) x= right;
		for(int j = 0; j < yn +2 ;j++){
			float y = (y0 + j) * deltaDegree;
			if(y < bottom) y = bottom;
			if(y > top) y = top;
			float xx,yy;
			CMapProjection* projection = info->map->getProjection();
			projection->getXY(x,y,&xx,&yy);
			if(j == 0){
				pDC->MoveTo(CPoint((int)xx,(int)yy));
			}else{
				pDC->LineTo(CPoint((int)xx,(int)yy));
			}
			if(j == 0){
				if(i == 0){
					//第一行不绘制，会重复
				}else{
					//横轴的坐标显示
					CString infoStr;
					infoStr.Format(_T("%d"),(int)x);
					projection->getXY(x,y+1,&xx,&yy);
					pDC->TextOutW(xx,yy,infoStr);
				}
			}
		}/*
		if(x >= left && x <= right){
			CString infoStr;
			float xx,yy;
			projection->getXY(x,bottom+1,&xx,&yy);
			float tl,tb;
			projection->getLB(xx,winRect.bottom,&tl,&tb);
			projection->getXY(tl,tb+1,&xx,&yy);
			infoStr.Format(_T("%d"),(int)x);
			pDC->TextOutW(xx,yy,infoStr);
		}*/
	}

}
