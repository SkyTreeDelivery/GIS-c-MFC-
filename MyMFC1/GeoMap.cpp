#include "stdafx.h"
#include "GeoMap.h"

CGeoMap::CGeoMap(CString name, int scale):Scale(scale),Name(name)
	, layerNum(0)
{
	projection = new CMapProjectionMercator();
}
CGeoMap::~CGeoMap()
{
	for(int i = 0; i < this->geoLayers.GetSize(); i++){
		if(geoLayers.GetAt(i)!=NULL)
			delete geoLayers.GetAt(i);
	}
}

void CGeoMap::setName(CString name)
{
	this->Name = name;
}
CString CGeoMap::getName()
{
	return this->Name;
}
int CGeoMap::getScale()
{
	return this->Scale;
}
void CGeoMap::addLayer(CGeoLayer* layer)
{
	this->geoLayers.Add(layer);
	layerNum++;
}
CGeoLayer* CGeoMap::getLayerAt(int index)
{
	return this->geoLayers.GetAt(index);
}
void CGeoMap::delLayerAt(int index)
{
	this->geoLayers.RemoveAt(index);
	layerNum--;
}
void CGeoMap::delLayerAll()
{
	this->geoLayers.RemoveAll();
	layerNum = 0;
}
void CGeoMap::setLayerIsVisible(CString layerName,boolean isVisable)
{
	for(int i = 0; i < geoLayers.GetSize(); i++)
	{
		CString name = geoLayers.GetAt(i)->getName();
		if(*name == *layerName){
			geoLayers.GetAt(i)->setVisible(isVisable); 
		}
	}
}
void CGeoMap::draw(CDCInfo* info)
{
	for(int i =  0; i < this->geoLayers.GetSize(); i++ ){
		this->geoLayers.GetAt(i)->draw(info);
	}
	info->map->getProjection()->draw(info);
}

void CGeoMap::clipMap(CRect clipRect){
	for(int i = 0; i < getLayerNum();i++){
		getLayerAt(i)->clipLayer(clipRect);
	}
}

void CGeoMap::project(){
	for(int i = 0; i < getLayerNum(); i++){
		getLayerAt(i)->project(projection);
	}
}
