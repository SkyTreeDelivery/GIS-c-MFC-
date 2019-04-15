#include "stdafx.h"
#include "GeoPolygon.h"


CGeoPolygon::CGeoPolygon(void)
{
	this->type = 4;
}
CGeoPolygon::~CGeoPolygon(void)
{
	for(int i = 0; i < this->points.GetSize(); i++){
		if(this->points.GetAt(i) != NULL)
			delete this->points.GetAt(i);
	}
}
void CGeoPolygon::addPoint(CPoint* point)
{
	this->points.Add(point);
}
CPoint* CGeoPolygon::getPointAt(int index)
{

	return this->points.GetAt(index);
}

void CGeoPolygon::delPointAt(int index)
{
	delete points.GetAt(index);
	this->points.RemoveAt(index);
}
	void CGeoPolygon::delPointAll()
{
	for(int i = 0; i < this->points.GetSize(); i++){
		delete this->points.GetAt(i);
	}
	this->points.RemoveAll();
}
int CGeoPolygon::getSize()
{
	return this->points.GetSize();
}

CPoint* CGeoPolygon::getPoints(){
	int size = getSize();
	CPoint* multiPoints = new CPoint[size];
	for(int i = 0;i < size;i++){
		multiPoints[i] = *(this->getPointAt(i));
	}
	return multiPoints;
}

void CGeoPolygon::draw(CDCInfo* info)
{
	//TODO
	
	/*int pointNum = getSize();
	rgb color = getColor();
	CPen pen;
	int lineWidth = 1;
	pen.CreatePen(PS_SOLID,lineWidth,RGB(0,0,0));
	pDC->SelectObject(&pen);
	for(int i = 0; i < pointNum; i++){
		if(i == 0){
			pDC->MoveTo(*getPointAt(i));
		}else{
			pDC->LineTo(*getPointAt(i));
		}
	}
	FloodFillPolygon(pDC);*/
	//绘制全部数据\
	
	/*int pointNum = getSize();

	CPen pen;
	int lineWidth = 1;
	pen.CreatePen(PS_SOLID,lineWidth,RGB(0,0,0));
	CPen* oldPen = (pDC->SelectObject(&pen));
	for(int i = 0; i < pointNum; i++){
		if(i == 0){
			pDC->MoveTo(*getPointAt(i));
		}else{
			pDC->LineTo(*getPointAt(i));
		}
	}
	if(clipPts.GetCount() != 0){
		pointNum = clipPts.GetCount();
		CPen redPen;
		redPen.CreatePen(PS_SOLID,lineWidth,RGB(255,0,0));
		pDC->SelectObject(&redPen);
		for(int i = 0; i < pointNum; i++){
			if(i == 0){
				pDC->MoveTo(*clipPts.GetAt(i));
			}else{
				pDC->LineTo(*clipPts.GetAt(i));
			}
		}
	}*/
	//drawChina(pDC);
	//drawBiszer(pDC);
	if(isOver(*(this->getRect()), info->clientRect_real)){
		drawSimpleArea(info);
		if(info->status == NO_ZOOMIN){
			drawClipAera(info);
		}
	}
}

void CGeoPolygon::drawChina(CDCInfo* info){
	CDC* pDC = info->pDC;
	//使用笔刷
	CBrush brush;
	rgb color = this->getPolygonColor();
	brush.CreateSolidBrush(RGB(color.r,color.g,color.b));
	pDC->SelectObject(&brush);
	int size = getSize();
	//创建临时polygon便于填充
	CPoint* multiPoints = new CPoint[size];
	for(int i = 0;i < size;i++){
		multiPoints[i] = *(this->getPointAt(i));
	}
	pDC->Polygon(multiPoints,size);
	CPen pen;
	int lineWidth = 1;
	pen.CreatePen(PS_SOLID,lineWidth,RGB(0,0,0));
	CPen* oldPen = (pDC->SelectObject(&pen));
	pDC->PolyBezier(multiPoints, size);
	delete[] multiPoints;

}

void CGeoPolygon::drawBiszer(CDCInfo* info){
	CDC* pDC = info->pDC;
	int pointNum = getSize();
	CPen pen;
	int lineWidth = 2;
	pen.CreatePen(PS_SOLID,lineWidth,RGB(255,0,0));
	CPen* oldPen = (pDC->SelectObject(&pen));
	for(int i = 0; i < pointNum; i++){
		if(i == 0){
			pDC->MoveTo(*getPointAt(i));
		}else{
			pDC->LineTo(*getPointAt(i));
		}
	}
	CPen pen1;
	lineWidth = 1;
	pen1.CreatePen(PS_SOLID,lineWidth,RGB(0,255,0));
	CPen* oldPen1 = (pDC->SelectObject(&pen1));
	/*CPoint* pts = new CPoint[pointNum];
	pointNum = pointNum/3 * 3 -2;
	for(int i = 0; i < pointNum; i++){
		pts[i] = *getPointAt(i);
	}*/
	//pDC->PolyBezier(pts, pointNum);
	//PolyBezier(pDC->GetSafeHdc(), pts, pointNum);

	if(isOver(*(this->getRect()),info->clientRect_real)){
		drawBiszer_my(info,getCArrayPts());
	}
}


void CGeoPolygon::drawClipAera(CDCInfo* info){
	for(int i = 0; i < clipPolygons.GetCount();i++){
		CGeoPolygon* polygon = clipPolygons.GetAt(i);
		CArray<CPoint*,CPoint*>* clipPts = polygon->getCArrayPts();
		if(clipPts->GetCount() >=2){
			CPoint p1 = *clipPts->GetAt(1);
				CPoint* p2 = clipPts->GetAt(2);
				CPoint pp = *p2;
		}

		if(clipPts->GetCount() != 0){
			CDC* pDC = info->pDC;
			int lineWidth = 1;
			CPen redPen;
			redPen.CreatePen(PS_SOLID,lineWidth,RGB(255,0,0));
			pDC->SelectObject(&redPen);
			drawBiszer_my(info,clipPts);
		}
	}
	
}

void CGeoPolygon::drawSimpleArea(CDCInfo* info){
	if(getCArrayPts()->GetCount() != 0){
		CDC* pDC = info->pDC;
		int lineWidth = 1;
		CPen redPen;
		redPen.CreatePen(PS_SOLID,lineWidth,RGB(0,255,0));
		pDC->SelectObject(&redPen);
		drawBiszer_my(info,getCArrayPts());
	}
}



CPoint getBiszerPoint(double t, CPoint p0, CPoint p1, CPoint p2, CPoint p3 ){
	double u = 1 - t;
	double tt = t*t;
	double uu = u*u;
	double uuu = uu*u;
	double ttt = tt*t;

	CPoint p;
	p.x = p0.x * uuu;
	p.y = p0.y* uuu;
	p.x += 3*p1.x * t*uu;
	p.y += 3*p1.y*t*uu;
	p.x += 3*p2.x * tt*u;
	p.y += 3*p2.y*tt*u;
	p.x += p3.x * ttt;
	p.y += p3.y*ttt;

	return p;
}

void CGeoPolygon::drawBiszer_my(CDCInfo* info, CArray<CPoint*,CPoint*>* points){
	CDC* pDC = info->pDC;
	int size = points->GetCount();
	static int sum = 0;
	sum++;
	CGeoMap* map = info->map;
	CArray<CPoint*, CPoint*>* pts;
	if(map->getHasPro() == false){	
		pts = this->getCArrayPts();
	}else{
		pts = this->getProPts();
	}
	
	//绘制普通矩形
	if(size <= 5){	
		for(int i = 0; i < size; i++){
			if(i == 0){
				pDC->MoveTo(*pts->GetAt(i));
			}else{
				pDC->LineTo(*pts->GetAt(i));
			}
		}
		return;
	}
	//绘制一般多边形
	int tsize = 10;
	//临时存储多个分割点
	CPoint* ptsSub = new CPoint[tsize+1];
	for(int i = 0; i < (size-1)/3; i++){
		for(int j = 0; j < tsize+1; j++){
			CPoint p = getBiszerPoint(1.0/tsize * j,*pts->GetAt(3*i), *pts->GetAt(3*i+1),*pts->GetAt(3*i+2),*pts->GetAt(3*i+3));
			ptsSub[j] = p;
		}
		for(int k = 0; k < tsize+1; k++){
			if(k == 0){
				pDC->MoveTo(ptsSub[k]);
			}else{
				pDC->LineTo(ptsSub[k]);
			}
		}
	}
}

void CGeoPolygon::FloodFillPolygon(CDC* pDC){
	CPoint* seed;
	int count = seeds.GetSize();
	rgb color = this->getPolygonColor();
	int x;
	int y;
	//填充颜色
	while(count >= 1){
		//取出种子点，直接填色
		seed = seeds.GetAt(count -1);
		seeds.RemoveAt(count - 1);
		x = seed->x;
		y = seed->y;
		pDC->SetPixel(seed->x,seed->y,RGB(color.r, color.g,color.b));
		//对周围的4个点做判断
		//下左右上
		if(pDC->GetPixel(x,y-1) == RGB(255,255,255)){
			seeds.Add(new CPoint(x,y-1));
		}
		if(pDC->GetPixel(x-1,y) == RGB(255,255,255)){
			seeds.Add(new CPoint(x-1,y));
		}
		if(pDC->GetPixel(x+1,y) == RGB(255,255,255)){
			seeds.Add(new CPoint(x+1,y));
		}
		if(pDC->GetPixel(x,y+1) == RGB(255,255,255)){
			seeds.Add(new CPoint(x,y+1));
		}
		count = seeds.GetSize();
	}

}

void CGeoPolygon::clipPolygon(CRect rect){
	if(isOver(*(this->getRect()), rect)){
		return;
	}
	CPoint* st;
	CPoint* en;
	clipPolygons.RemoveAll();
	int stCode,enCode;
	CPoint leftTop = rect.TopLeft();
	CPoint leftBottom = CPoint(rect.left,rect.bottom);
	CPoint rightTop = CPoint(rect.right,rect.top);
	CPoint rightBottom = CPoint(rect.right,rect.bottom);
	int* t = 0;
	CPoint* cross;
	boolean isInclipArea = false;
	CGeoPolygon* polygon = new CGeoPolygon;
	for(int i = 0; i < getSize() - 1; i++){
		st = getPointAt(i);
		en = getPointAt(i+1);
		//计算code
		stCode = getCode(rect, *st);
		enCode = getCode(rect, *en);
		if(stCode == 0 && enCode == 0){ // 始末点都在内部
			if(isInclipArea == false){
				polygon = new CGeoPolygon;
				clipPolygons.Add(polygon);
				polygon->addPoint(st);
			}else{
				polygon->addPoint(st);
			}
			
		}else if(stCode & enCode == 1){ // 始末点都在外部
						
		}else if(stCode == 0 || enCode == 0){ // 有一个点在内部
			if(isInclipArea = false){
				isInclipArea = true;
				polygon = new CGeoPolygon;
				clipPolygons.Add(polygon);
				CPoint* pt = getCrossRectPoint(*st,*en,clipRect);
				polygon->addPoint(pt);
			}else{
				polygon->addPoint(st);
				isInclipArea = false;
				CPoint* pt = getCrossRectPoint(*st,*en,clipRect);
				polygon->addPoint(pt);
			}
		}else { // 都在外部的不同部位
			CArray<CPoint*,CPoint*>* pts = getCrossRectPointTh(*st,*en,rect);
			if(pts->GetCount() != 0){
				polygon = new CGeoPolygon;
				clipPolygons.Add(polygon);
				for(int i = 0; i < pts->GetCount();i++){
					polygon->addPoint(pts->GetAt(i));
				}
			}
		}
	}
}

void CGeoPolygon::project(CMapProjection* projection){
	for(int i = 0; i < getSize();i++){
		CPoint* pt = points.GetAt(i);
		float x,y;
		projection->getXY(pt->x*1.0/MULTI,pt->y*1.0/MULTI,&x,&y);
		CPoint* ptPro = new CPoint((int)x,(int)y);
		proPts.Add(ptPro);
	}
}