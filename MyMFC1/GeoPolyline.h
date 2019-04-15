#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "MapProjection.h"
class CGeoPolyline :public CGeoObject
{
public:
	CGeoPolyline(void);
	~CGeoPolyline(void);
	void addPoint(CPoint* point);
	CPoint* getPointAt(int index);
	void delPointAt(int index);
	void delPointAll();
	int getSize();
	void draw(CDCInfo* info);
	void setLineWidth(double lineWidth){
		this->lineWidth = lineWidth;
	}
	double getLineWidth(){
		return this->lineWidth;
	}
	void setLineColor(int r,int g,int b){
		this->lineColor.r = r;
		this->lineColor.g = g;
		this->lineColor.b = b;
	}
	rgb getLineColor(){
		return this->lineColor;
	}
	void clipPolyline(CRect* rect);
	CPoint* getPoints();
	CArray<CPoint*,CPoint*>* getCArrayPts(){
		return &points;
	}
	CArray<CPoint*,CPoint*>* getProPts(){
		return &proPts;
	}
	void project(CMapProjection* projection);
private:
	CArray<CPoint*,CPoint*> points;
	CArray<CPoint*,CPoint*> proPts;
	double lineWidth;
	rgb lineColor;
};

