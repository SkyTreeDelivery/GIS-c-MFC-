#pragma once
#include "GeoMap.h"

class CDCInfo
{
public:
	CDCInfo(void);
	~CDCInfo(void);
public:
	CRect viewRect;    //�ӿڴ�С��������ʾ���ݵľ��ο��С����������ת����
	CRect winRect;		//�߼������С
	CRect clientRect;   //�û��ɲ����ľ��ο��С
	CRect clientRect_real;	//ת��Ϊ�߼�������û���
	CDC* pDC;	//���ƵĻ���
	int status;		//�������ܵ�ѡ��״̬
	CGeoMap* map;		//�������ݵ�map���ᵼ�½�����������⣩

};

