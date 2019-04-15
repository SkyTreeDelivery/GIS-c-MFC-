#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "MapProjection.h"
class CGeoPolygon :	public CGeoObject
{
public:
	CGeoPolygon(void);
	~CGeoPolygon(void);
	void addPoint(CPoint* point);
	CPoint* getPointAt(int index);
	void delPointAt(int index);
	void delPointAll();
	int getSize();
	void draw(CDCInfo* info);
	void drawBiszer(CDCInfo* info);
	void drawChina(CDCInfo* info);
	void drawBiszer_my(CDCInfo* info, CArray<CPoint*,CPoint*>* points);
	void drawClipAera(CDCInfo* info);
	void drawSimpleArea(CDCInfo* info);
	void setLineColor(int r,int g,int b){
		this->polygonColor.r = r;
		this->polygonColor.g = g;
		this->polygonColor.b = b;
	}
	rgb getPolygonColor(){
		return this->polygonColor;
	}
	void FloodFillPolygon(CDC* pDC);
	rgb getColor(){
		return polygonColor;
	}
	CArray<CPoint*,CPoint*> seeds;
	void clipPolygon(CRect rect);
	CArray<CGeoPolygon*,CGeoPolygon*> clipPolygons;
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
	rgb polygonColor;
};
