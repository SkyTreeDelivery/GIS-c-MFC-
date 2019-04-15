#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "GeoObject.h"
class CGeoObject
{
public:
	CGeoObject(void);
	~CGeoObject(void);
	void setName(CString name);
	CString getName() const;
	void setId(int id);
	int getId() const;
	void setRect(CRect* rect);
	void setRect(int x1,int x2,int width,int height);
	void setType(int type){
		this->type = type;
	}
	int getType(){
		return this->type;
	}
	CRect* getRect() const;
	virtual void draw(CDCInfo* info) = 0;
	int getCode(CRect wcRect, CPoint pt);
	CRect clipRect;
	CPoint* getCrossRectPoint(CPoint st, CPoint en, CRect rect);
	CArray<CPoint*,CPoint*>* getCrossRectPointTh(CPoint st, CPoint en, CRect rect);
	int getDirction(int code);
	void virtual project(CMapProjection* projection) = 0;
private:
	CString name;
	int id;
	CRect* wcRect;
protected:
	int type;
public:
	CRect* getEnvelope(CArray<CPoint*,CPoint*>* pts);
	boolean isOver(CRect ro, CRect rt);
};

