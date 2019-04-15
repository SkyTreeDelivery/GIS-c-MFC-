#include "stdafx.h"
#include "DCInfo.h"


CDCInfo::CDCInfo(void)
{
	status = -1;
	map = NULL;
}


CDCInfo::~CDCInfo(void)
{
	if(pDC!= NULL)
		delete *pDC;
	if(map != NULL){
		delete map;
	}
}
