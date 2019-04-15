#pragma once
#include "GeoMap.h"

class CDCInfo
{
public:
	CDCInfo(void);
	~CDCInfo(void);
public:
	CRect viewRect;    //视口大小（用于显示数据的矩形框大小，用于坐标转换）
	CRect winRect;		//逻辑坐标大小
	CRect clientRect;   //用户可操作的矩形框大小
	CRect clientRect_real;	//转换为逻辑坐标的用户框
	CDC* pDC;	//绘制的画布
	int status;		//操作功能的选择状态
	CGeoMap* map;		//存数数据的map（会导致交叉包含的问题）

};

