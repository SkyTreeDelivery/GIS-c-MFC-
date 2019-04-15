
#include "stdafx.h"
#include "GeoPoint.h"


CGeoPoint::CGeoPoint(int x, int y)
{
	this->point.SetPoint(x,y);
	type = 1;
}
CGeoPoint::CGeoPoint(){
	type = 1;
};
CGeoPoint::~CGeoPoint(void)
{
}
void CGeoPoint::setPoint(int x, int y)
{
	this->point.SetPoint(x,y);
}

void CGeoPoint::setPoint(CPoint point)
{
	this->point = point;
}
CPoint CGeoPoint::getPoint() const
{
	return this->point;
}
void CGeoPoint::draw(CDCInfo* info)
{
	//TODO
	CDC* pDC = info->pDC;
	pDC->SetPixel(point.x,point.y,RGB(255,0,0));
}

//这种方法应该写在各自的类中
void CGeoPoint::project(CMapProjection* projection){
	CPoint* pt = &getPoint();
	float x,y;
	projection->getXY(pt->x*1.0/MULTI,pt->y*1.0/MULTI,&x,&y);
	proPt = CPoint((int)x,(int)y);
}

