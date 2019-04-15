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
	//���ᣬ���ᣬ���ʣ���һƫ���ʣ��ڶ�ƫ����
	double a,b,ae,e1,e2;
	//ͶӰ����
	void virtual getXY(float l,float b,float *x, float *y) = 0;
	//ͶӰ����
	void virtual getLB(float x , float y, float *L,float*B) = 0;
	void virtual draw(CDCInfo* info );
	double N;
	double K;
};

