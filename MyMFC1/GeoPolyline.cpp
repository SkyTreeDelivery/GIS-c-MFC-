#include "stdafx.h"
#include "GeoPolyline.h"
#include "cmath"


CGeoPolyline::CGeoPolyline(void)
	: lineWidth(0)
{
	this->type = 2;
}
CGeoPolyline::~CGeoPolyline(void)
{
	for(int i = 0; i < this->points.GetSize(); i++){
		if(this->points.GetAt(i))
			delete this->points.GetAt(i);
	}
}
void CGeoPolyline::addPoint(CPoint* point)
{
	this->points.Add(point);
}
CPoint* CGeoPolyline::getPointAt(int index)
{
	return this->points.GetAt(index);
	
}
void CGeoPolyline::delPointAt(int index)
{
	this->points.RemoveAt(index);
}
	void CGeoPolyline::delPointAll()
{
	this->points.RemoveAll();
}
int CGeoPolyline::getSize()
{
	return this->points.GetSize();
}

CPoint* CGeoPolyline::getPoints(){
	int size = getSize();
	CPoint* multiPoints = new CPoint[size];
	for(int i = 0;i < size;i++){
		multiPoints[i] = *(this->getPointAt(i));
	}
	return multiPoints;
}

void CGeoPolyline::draw(CDCInfo* info)
{
	//TODO
	CDC* pDC = info->pDC;
	int size = getSize();
	rgb color = getLineColor();
	CPen pen;
	pen.CreatePen(PS_SOLID,lineWidth,RGB(color.r,color.g,color.b));
	pDC->SelectObject(&pen);

	CGeoMap* map = info->map;
	CArray<CPoint*,CPoint*>* pts;
	if(map->getHasPro() == false){	
		pts = this->getCArrayPts();
	}else{
		pts = this->getProPts();
	}
	for(int i = 0; i < size; i++){
			if(i == 0){
				pDC->MoveTo(*pts->GetAt(i));
			}else{
				pDC->LineTo(*pts->GetAt(i));
			}
		}
	
	
		/*CPoint* start = this->getPointAt(0);
		CPoint* end = this->getPointAt(1);
		double x1 = start->x;
		double y1 = start->y;
		double x2 = end->x;
		double y2 = end->y;
		double dx = x2 - x1;
		double dy = y2 - y1;
		int n = abs((int)dx) > abs((int)dy)? abs((int)dx) : abs((int)dy);
		dy = dy/n;
		dx = dx/n;
		double x = x1;
		double y = y1;
		for(int i = 0; i < n - 1; i++){
			pDC->SetPixel((int)(x+600),(int)(y),RGB(255,0,0));
			x = (int)(x + dx);
			y = (int)(y + dy);
		}*/
}

void CGeoPolyline::project(CMapProjection* projection){
	for(int i = 0; i < getSize();i++){
		CPoint* pt = points.GetAt(i);
		float x,y;
		projection->getXY(pt->x*1.0/MULTI,pt->y*1.0/MULTI,&x,&y);
		CPoint* ptPro = new CPoint((int)x,(int)y);
		proPts.Add(ptPro);
	}
}

