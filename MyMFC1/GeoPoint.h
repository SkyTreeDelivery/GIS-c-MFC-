#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "MapProjection.h"
class CGeoPoint :public CGeoObject
{
public:
	CGeoPoint(int x,int y);
	CGeoPoint();
	~CGeoPoint(void);
	void setPoint(int x, int y);
	void setPoint(CPoint point);
	CPoint getPoint() const;
	void draw(CDCInfo* info);
	CPoint* getProPoint(){
		return &proPt;
	}
	void setProPoint(CPoint pt){
		proPt = pt;
	}
	void project(CMapProjection* projection);
private:
	CPoint point;
	CPoint proPt;
};
