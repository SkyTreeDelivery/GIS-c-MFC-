#pragma once
#include "stdafx.h"
#include "MapProjection.h"
#include "DCInfo.h"
#include "GeoObject.h"
class CGeoLayer
{
public:
	CGeoLayer(void);
	~CGeoLayer(void);
	void setName(CString name);
	CString getName();
	boolean isVisible();
	void setVisible(boolean isVisible);
	void addObject(CGeoObject* geoObject);
	CGeoObject* getObjectAt(int index);
	void delObjectAt(int index);
	void delObjectAll();
	void draw(CDCInfo* info);
	int getSize(){
		return geoObjects.GetSize();
	}
	int getObjsNum(){
		return this->geoObjects.GetSize();
	}
	void clipLayer(CRect clipRect);
	CRect clipRect;
	void initLayerRect();
	void project(CMapProjection* projection);
private:
	CString name;
	boolean visible;
	CRect crRect;
	CArray<CGeoObject*, CGeoObject*> geoObjects;
};
