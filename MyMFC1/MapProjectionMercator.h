#pragma once
#include "stdafx.h"
#include "DCInfo.h"
#include "MapProjection.h"
class CMapProjectionMercator :
	public CMapProjection
{
public:
	CMapProjectionMercator(void);
	~CMapProjectionMercator(void);
	void getXY(float l,float b,float *x, float *y);
	void getLB(float x , float y, float *L,float*B);
};

