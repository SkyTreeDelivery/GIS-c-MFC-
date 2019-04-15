#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "GeoLayer.h"
#include "MapProjection.h"
class CGeoMap
{
public:
	CGeoMap(CString name,int scale);
	~CGeoMap(void);
	void setName(CString name);
	CString getName();
	void setScale(int mapScale);
	int getScale();
	void addLayer(CGeoLayer* layer);
	CGeoLayer* getLayerAt(int index);
	void delLayerAt(int index);
	void delLayerAll();
	void setLayerIsVisible(CString layerName,boolean isVisable);
	void draw(CDCInfo* info);

	void setLoaded(boolean b){
		this->isMapLoaded = b;
	}
	boolean getLoaded(){
		return isMapLoaded;
	}
	void setProjection(CMapProjection* pro){
		this->projection = pro;
	}
	CMapProjection* getProjection(){
		return projection;
	}
	void setHasPro(boolean b){
		this->hasProjection = b;
	}
	boolean getHasPro(){
		return hasProjection;
	}
	void setRect(CRect* rect){
		this->crRect = rect;
	}
	CRect getRect(){
		return this->crRect;
	}
	int getLayerNum(){
		return this->layerNum;
	}
	void clipMap(CRect clipRect);
	void project();
	CRect clipRect;
private:
	CString Name;
	int const Scale;
	CRect crRect;
	CArray<CGeoLayer*,CGeoLayer*> geoLayers;
protected:
	int Type;
	boolean isMapLoaded;
	boolean hasProjection;
	CMapProjection* projection;
private:
	int layerNum;
};
