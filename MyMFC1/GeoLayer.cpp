#include "stdafx.h"
#include "GeoLayer.h"

CGeoLayer::CGeoLayer(void)
{
}
CGeoLayer::~CGeoLayer(void)
{
	for(int i = 0; i < this->geoObjects.GetSize(); i++){
		if(geoObjects.GetAt(i)!=NULL)
			delete this->geoObjects.GetAt(i);
	}
}

void CGeoLayer::setName(CString name)
{
	this->name = name;
}
CString CGeoLayer::getName()
{
	return this->name;
}

boolean CGeoLayer::isVisible()
{
	return this->visible;
}

void CGeoLayer::setVisible(boolean isVisible)
{
	this->visible = isVisible;
}
void CGeoLayer::addObject(CGeoObject* geoObject)
{
	this->geoObjects.Add(geoObject);
}
CGeoObject* CGeoLayer::getObjectAt(int index)
{
	return this->geoObjects.GetAt(index);
}
void CGeoLayer::delObjectAt(int index)
{
	this->geoObjects.RemoveAt(index);
}
void CGeoLayer::delObjectAll()
{
	this->geoObjects.RemoveAll();
}

void CGeoLayer::initLayerRect(){
	int objNum = getSize();
	int top,left,bottom,right;
	for(int i = 0; i < objNum; i++){
		CGeoObject* obj = getObjectAt(i);
		if( i == 0){
			CRect* rect;
			if(obj->getType() == 2){
				rect = obj->getEnvelope(((CGeoPolyline*)obj)->getCArrayPts());
				top = rect->top;
				left = rect->left;
				right = rect->right;
				bottom = rect->bottom;
			}else if(obj->getType() == 4){
				rect = obj->getEnvelope(((CGeoPolygon*)obj)->getCArrayPts());
				top = rect->top;
				left = rect->left;
				right = rect->right;
				bottom = rect->bottom;
			}
			
		}
		if(obj->getType() == 2){
			 CRect* rect = obj->getEnvelope(((CGeoPolyline*)obj)->getCArrayPts());
			 if(rect->top > top) top = rect->top;
			 if(rect->top > top) left = rect->left;
			 if(rect->top > top) bottom = rect->bottom;
			 if(rect->top > top) right = rect->right;
			 obj->setRect(rect);
		}else if(obj->getType() == 4){
			 CRect* rect = obj->getEnvelope(((CGeoPolygon*)obj)->getCArrayPts());
			 if(rect->top > top) top = rect->top;
			 if(rect->top > top) left = rect->left;
			 if(rect->top > top) bottom = rect->bottom;
			 if(rect->top > top) right = rect->right;
			 obj->setRect(rect);
		}
	}
	this->crRect = CRect(left,top,right,bottom);
}


void CGeoLayer::draw(CDCInfo* info)
{
	for(int i = 0; i < this->geoObjects.GetSize(); i++){
		this->geoObjects.GetAt(i)->draw(info);
	}
}

void CGeoLayer::clipLayer(CRect clipRect){
	for(int i = 0; i < getObjsNum(); i++){
		//根据不同的类型选用不同的绘制方法
		if(getObjectAt(i)->getType() == 4){
			((CGeoPolygon*)getObjectAt(i))->clipPolygon(clipRect);
		}
		else if(getObjectAt(i)->getType() == 2){
			//((CGeoPolyline*)getObjectAt(i))->clipPolygon(clipRect);
		}
	}
}

void CGeoLayer::project(CMapProjection* projection){
	for(int i = 0; i < getObjsNum(); i++){
		getObjectAt(i)->project(projection);
	}
}
