#include "stdafx.h"
#include "MapProjectionMercator.h"
#include "math.h"
# define PI 3.14159265358979323846
# define E 2.71828

CMapProjectionMercator::CMapProjectionMercator(void)
{
}


CMapProjectionMercator::~CMapProjectionMercator(void)
{
}

//正解公式
void CMapProjectionMercator::getXY(float l,float b,float *x, float *y){
	//考虑了地球椭球
	*y = K* log(tan(PI*45/180 + (b/2)*PI/180));/**pow((1-ae*sin(b))/(1+ae*sin(b)),ae/2))*/
	*x = K*(l-L0)*PI/180;
}
//反解公式
void CMapProjectionMercator::getLB(float x , float y, float *l,float*b){
	//更为准确的考虑地球椭球的反解公式需要迭代计算或微分估计法（暂时不考虑）
	//*b = PI/2 - 2*atan(exp(-x/K)*exp((E/2)*log((1-ae*sin(b))/(1+ae*sin(b))));
	*b =  (2*atan(exp(x/K)) - PI/2)*180/PI;
	*l = y*180/(K*PI) + L0;
}

