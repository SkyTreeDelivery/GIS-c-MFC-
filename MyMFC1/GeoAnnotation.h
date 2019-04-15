#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "MapProjection.h"
class CGeoAnnotation :
	public CGeoObject
{
public:
	CGeoAnnotation(void);
	~CGeoAnnotation(void);
	void draw(CDCInfo* info);

	void setLocation(int x,int y){
		location = CPoint(x,y);
		this->x = x;
		this->y = y;
	}
	void setLocation(CPoint pt){
		this->location = pt;
		this->x = pt.x;
		this->y = pt.y;
	}
	CPoint getLocation(){
		return this->location;
	}
	void setAnno(CString anno){
		this->anno = anno;
	}
	CString getAnno(){
		return anno;
	}
	void project(CMapProjection* projection);
private:
	CPoint location;
	CPoint proPt;
	CString anno;
	int x,y;
};

