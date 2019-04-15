#pragma once
#include "stdafx.h"
#include "DCInfo.h"
class CDCInfo;
class CMapProjection
{
public:
	CMapProjection(void);
	~CMapProjection(void);
	double L0,B0;
	//长轴，短轴，扁率，第一偏心率，第二偏心率
	double a,b,ae,e1,e2;
	//投影正解
	void virtual getXY(float l,float b,float *x, float *y) = 0;
	//投影反解
	void virtual getLB(float x , float y, float *L,float*B) = 0;
	void virtual draw(CDCInfo* info );
	double N;
	double K;
};

