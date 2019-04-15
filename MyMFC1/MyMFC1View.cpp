
// MyMFC1View.cpp : CMyMFC1View 类的实现
//

#include "stdafx.h"
#include <cmath>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyMFC1.h"
#endif

#include "MyMFC1Doc.h"
#include "MyMFC1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#
// CMyMFC1View


IMPLEMENT_DYNCREATE(CMyMFC1View, CView)

BEGIN_MESSAGE_MAP(CMyMFC1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CMyMFC1View::OnFileOpen)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_ZOOMIN, &CMyMFC1View::OnButtonZoomin)
	ON_COMMAND(ID_BUTTON_ALL, &CMyMFC1View::OnButtonAll)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BUTTON_TRANSLATION, &CMyMFC1View::OnButtonTranslation)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMyMFC1View 构造/析构

CMyMFC1View::CMyMFC1View()
{
	// TODO: 在此处添加构造代码
	map = NULL;
	pros = NULL;
	info = NULL;
	isPressed = false;
	this->status = ZOOMIN;
	MemDC = NULL;
}

CMyMFC1View::~CMyMFC1View()
{
	if(map != NULL){
		delete map;
	}
	if(MemDC != NULL){
		delete MemDC;
	}
}

BOOL CMyMFC1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


// CMyMFC1View 绘制
void CMyMFC1View::OnDraw(CDC* pDC)
{
	CMyMFC1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if(info == NULL){
		info = new CDCInfo;
	}
	if(map != NULL){
		if(map->getLoaded() == false){
			info->pDC = pDC;
			info->map = map;
			GetClientRect(&(info->clientRect));
		}
		//map->draw(info);
		bufferedDraw(pDC);
	}
}

void CMyMFC1View::bufferedDraw(CDC* pDC){
	
	//这时还不能绘图，因为没有地方画 ^_^
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	CRect client;
	GetClientRect(&client);
	int nWidth = client.Width();
	int nHeight= client.Height();

	if(MemDC == NULL){
		MemDC = new CDC();
		//随后建立与屏幕显示兼容的内存显示设备
		MemDC->CreateCompatibleDC(pDC);
		MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
		CBitmap *pOldBit= MemDC->SelectObject(&MemBitmap);
	}
	OnPrepareDC(MemDC);
	CRect realClient = client;
	pDC->DPtoLP(&realClient);
	MemDC->FillSolidRect(realClient,pDC->GetBkColor());

	//绘图
	CDC* oldpDC =NULL;
	if(map != NULL && info !=NULL){
		if(isPressed != true){
		    oldpDC = info->pDC;
			info->pDC = MemDC;
			map->draw(info);
			info->pDC = oldpDC;
		}
	}

	//将内存中的图拷贝到屏幕上进行显示
	//pDC->BitBlt(0,0,nWidth,nHeight,MemDC,0,0,SRCCOPY);
	CPoint delta = ProDelta(pDC,deltaAll);
	pDC->StretchBlt(realClient.left,realClient.top,realClient.Width(),realClient.Height(),MemDC,realClient.left - delta.x,realClient.top - delta.y,realClient.Width(),realClient.Height(),SRCCOPY);
 	upPoint = CPoint(0,0);
	downPoint = upPoint;
}


// CMyMFC1View 打印

BOOL CMyMFC1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyMFC1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyMFC1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyMFC1View 诊断

#ifdef _DEBUG
void CMyMFC1View::AssertValid() const
{
	CView::AssertValid();
}

void CMyMFC1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMFC1Doc* CMyMFC1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFC1Doc)));
	return (CMyMFC1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFC1View 消息处理程序


void CMyMFC1View::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	//打开dialog
	CFileDialog fDlg(true);
	if(fDlg.DoModal()!= IDOK)return;
	CString fileName = fDlg.GetPathName();
	USES_CONVERSION;
	char* filename = T2A(fileName);
	FILE* fp;
	fopen_s(&fp,filename,"r");

	//得到颜色配置文件的输入流
	FILE* fp_color;
	char* excelPath;
	/*int maxIndex = fileName.GetLength();
	filename[maxIndex -3] = 'o';
	filename[maxIndex -2] = 'p';
	filename[maxIndex -1] = 't';*/
	fopen_s(&fp_color,"D:\\我的用户\\新建文件夹\\c++地图数据\\china1.opt","r");
	excelPath = "D:\\我的用户\\新建文件夹\\c++地图数据\\chnCity.xls";
	//获得数据
	if(fp == NULL){
		MessageBox(TEXT("File Open Failed"));
		return;
	}	
	if( map!= NULL){
		delete map;
	}
	map = new CGeoMap(CString("地图"),1);
	if(fileName.Right(9) == "wuhan.txt"){
		map->setLoaded(false);
		map->setHasPro(false);
		readWuhanData(fp);
	}else if(fileName.Right(10) == "china1.txt"){
		map->setLoaded(false);
		map->setHasPro(false);
		readChinaData(fp);
	}else if(fileName.Right(10) == "china1.dat"){
		map->setLoaded(true);
		map->setHasPro(false);
		readChinaRealData(fp);
		readColorFile(fp_color);
		addProsData();
		readExcelData(excelPath);
	}else if(fileName.Right(15) == "chnFillTest.txt"){
		map->setLoaded(false);
		map->setHasPro(false);
		readFloodFillData(fp);
	}else if(fileName.Right(12) == "clipData.txt"){
		map->setLoaded(true);
		map->setHasPro(false);
		readClipData(fp);
	}else if(fileName.Right(14) == "BOUNT_line.mif"){
		map->setLoaded(true);
		map->setHasPro(true);
		//map->setProjection(new CMapProjectionMercator());
		readBLData(fp);
	}
	if(map->getHasPro() == true){
		map->project();
		CMapProjection* pro = map->getProjection();
		float x,y;
		pro->getXY(rect.left/MULTI,rect.top/MULTI,&x,&y);
		rect.left = (int)x;
		rect.top = (int)y;
		pro->getXY(rect.right/MULTI,rect.bottom/MULTI,&x,&y);
		rect.right = (int)x;
		rect.bottom = (int)y;
	}
	//释放资源
	fclose(fp);
	Invalidate();
}
//武汉的数据是很多个直线
void CMyMFC1View::readWuhanData(FILE* fp)
{
	int x1,y1,x2,y2;
	CGeoLayer* layer = new CGeoLayer();
	while(!feof(fp)){
		CGeoObject* obj = new CGeoPolyline();
		fscanf_s(fp,"%d%d%d%d",&x1,&y1,&x2,&y2);
		((CGeoPolyline*)obj)->addPoint(new CPoint(x1,y1));
		((CGeoPolyline*)obj)->addPoint(new CPoint(x2,y2));
		layer->addObject(obj);
	}
	map->addLayer(layer);
}


void CMyMFC1View::readChinaData(FILE* fp)
{
	int x1,y1;
	CGeoLayer* layer = new CGeoLayer();
	while(!feof(fp)){
		CGeoObject* obj = new CGeoPoint();
		fscanf_s(fp,"%d%d",&x1,&y1);
		((CGeoPoint*)obj)->setPoint(CPoint(x1,y1));
		layer->addObject(obj);
	}
	map->addLayer(layer);
}

void CMyMFC1View::readChinaRealData(FILE* fp){
	//读取文件头
	//上下左右
	int top,bottom,left,right;
	//总层数，某一层名
	int layerNum,nameLength;
	CString* layerName = NULL;
	char* layerNameChar;
	int targetNum,type;
	int x,y;
	//总文件头
	fscanf_s(fp,"%d,%d",&left,&top);
	fscanf_s(fp,"%d,%d",&right,&bottom);
	fscanf_s(fp,"%d",&layerNum);
	map->setRect(new CRect(left,top,right,bottom));
	rect = CRect(left,top,right,bottom);
	//层文件头
	for(int i = 0; i < layerNum; i++){
		//读取层名长度
		fscanf_s(fp,"%d",&nameLength);
		//读取layer的名字
		layerNameChar = new char[nameLength+1];
		char symbol[1];
		//读取转义字符
		fread(symbol,sizeof(char),1,fp);
		layerNameChar[nameLength] = '\0';
		//读取图层名
		fread(layerNameChar,sizeof(char),nameLength,fp);
		layerName = new CString(layerNameChar);
		//读取要素object的数目
		fscanf_s(fp,"%d",&targetNum);
		//正式读取空间数据
		CGeoLayer* layer = new CGeoLayer();
		layer->setName(*layerName);
		for(int j = 0; j < targetNum;j++){
			//读取目标类型
			fscanf_s(fp,"%d",&type);
			if(type == 1){
				CGeoPolyline* polyline = new CGeoPolyline();
				fscanf_s(fp,"%d,%d",&x,&y);
				CPoint* point = new CPoint(x,y);
				while(x != -99999&& y != -99999){
					polyline->addPoint(point);
					fscanf_s(fp,"%d,%d",&x,&y);
					point = new CPoint(x,y);
				}
				layer->addObject(polyline);	
			}else if(type == 2){
				CGeoPolygon* polygon = new CGeoPolygon();
				fscanf_s(fp,"%d,%d",&x,&y);
				CPoint* point = new CPoint(x,y);
				while(x != -99999&& y != -99999){
					polygon->addPoint(point);
					fscanf_s(fp,"%d,%d",&x,&y);
					point = new CPoint(x,y);
				}
				layer->addObject(polygon);	
			}		
		}
		map->addLayer(layer);
	}
}

void CMyMFC1View::readFloodFillData(FILE* fp){
	int count;
	int pointNum;
	CGeoLayer* layer = new CGeoLayer;
	map->addLayer(layer);
	int x,y;
	int color;
	while(true){
		fscanf_s(fp,"%d",&count);
		if(count == -1){
			break;
		}
		//循环多边形
		for(int i = 0; i < count; i++){
			fscanf_s(fp,"%d",&pointNum);
			CGeoPolygon* polygon = new CGeoPolygon;
			polygon-> setType(2);
			for(int j = 0; j < pointNum; j++){
				fscanf_s(fp,"%d%d",&x,&y);
				CPoint* point = new CPoint(x,y);
				polygon->addPoint(point);
			}
			//读取种子点
			layer->addObject(polygon);
		}
		fscanf_s(fp,"%d%d",&x,&y);
		((CGeoPolygon*)(layer->getObjectAt(layer->getObjsNum()-1)))->seeds.Add(new CPoint(x,y));
		fscanf_s(fp,"%d",&color);
		rgb c = convertColor(color);
		for(int i = 0; i < count; i++){
			int size = layer->getObjsNum();
			((CGeoPolygon*)(layer->getObjectAt(size-1-i)))->setLineColor(c.r,c.g,c.b);
		}
	}
	map->getLayerAt(0);
}

void CMyMFC1View::readClipData(FILE* fp){
	CRect* wcRect = new CRect();
	fscanf_s(fp,"%d%d",&(*wcRect).left,&(*wcRect).bottom);
	fscanf_s(fp,"%d%d",&(*wcRect).top,&(*wcRect).right);
	map->setRect(wcRect);
	this->rect = wcRect;
	CGeoLayer* layer =new CGeoLayer;
	map->addLayer(layer);
	int ptsNum;
	int x,y;
	int count = 0;
	fscanf_s(fp,"%d",&ptsNum);
	while(ptsNum != -9999){
		count++;
		CGeoPolygon* polygon = new CGeoPolygon;
		layer->addObject(polygon);
		for(int i = 0; i < ptsNum; i++){
			fscanf_s(fp,"%d%d",&x,&y);
			CPoint* point = new CPoint(x,y);
			polygon->addPoint(point);
		}
		fscanf_s(fp,"%d",&ptsNum);
	}
	//更新layer中的obj的wcrect
	layer->initLayerRect();
}


rgb CMyMFC1View::convertColor(int color){
		rgb c;
		c.r = byte((color >> 16) & 255);
		c.g = byte((color>> 8) & 255);
		c.b = byte((color >> 0) & 255);
		return c;
}

//用于显示数据，在进入这个方法之前，rect所显示的逻辑坐标就应当被设置好
void CMyMFC1View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
		// TODO: Add your specialized code here and/or call the base class
	//添加一个bool变量，控制是否是最新需要变换的这个数据加载，如果没有加载，则不需要坐标变换
	if(map == NULL){
		return;
	}
	if( !map->getLoaded()) 
		return;
	CSize winSize; 
	CPoint winPt;	
	CRect winRectD;
	CSize clientSize;
	CPoint clientPoint;
	CSize viewSize;
	CPoint viewPt;
	CRect clientView;
		 
	this->GetClientRect(&clientView);//取得客户区矩形区域大小
	clientSize = clientView.Size();
	clientPoint = clientView.CenterPoint();//取得客户区矩形区域中心点坐标
	double clientRadio = clientSize.cx/clientSize.cy;
	winSize = rect.Size();  //设定窗口对应尺寸
	winPt =  rect.CenterPoint(); //设置窗口中心为对应原点
	
	/*(info != NULL){
		delete info;
	}*/
	info = new CDCInfo;
	info->map = map;
	info->status = status;
	info->clientRect = clientView;

	double radio = -winSize.cx*1.0/winSize.cy;
	CPoint tl = clientView.TopLeft();
	if(abs(radio)>clientRadio){
		viewSize.cy = clientSize.cx/radio;
		viewSize.cx = clientSize.cx;
		tl.y = tl.y + (clientSize.cy - viewSize.cy)/2;
	}else{
		viewSize.cx = clientSize.cy*radio;
		viewSize.cy = clientSize.cy;
		tl.x = tl.x + (clientSize.cx - viewSize.cx)/2;
	}
	viewPt = clientView.CenterPoint();

	
	info->viewRect = CRect(tl, viewSize);
	info->winRect = rect;
	
	pDC->SetMapMode(MM_ANISOTROPIC); //设置指定设备环境的映射方式
	pDC->SetViewportExt(viewSize);  //设定视口尺寸
	pDC->SetViewportOrg(viewPt); //设置视口中心为坐标系原点
	pDC->SetWindowExt(winSize);   //设置窗口长宽
	pDC->SetWindowOrg(winPt);	//设置窗口原点

	info->pDC = pDC;
	CPoint topLeft = clientView.TopLeft();
	CPoint bottomRight = clientView.BottomRight();
	pDC->DPtoLP(&topLeft);
	pDC->DPtoLP(&bottomRight);
	info->clientRect_real = CRect(topLeft,bottomRight);
	CView::OnPrepareDC(pDC, pInfo);
}

void CMyMFC1View::readColorFile(FILE* fp)
{
	int r;
	int g;
	int b;
	int layerNum;
	char* layerNameChar;
	int hasPolyline;
	double lineWidth;
	rgb polylineColor;
	int hasPolygon;
	rgb polygonColor;
	fscanf_s(fp,"%d",&layerNum);
	pros = new layerPropotry[layerNum];
	layerPropotry* pro;
	for(int i= 0; i < layerNum;i++){
		pro = pros + i;
		//读取层名
		//读取\n
		char symbol;
		fread(&symbol,sizeof(char),1,fp);
		//读取名字
		layerNameChar = new char[30];
		for(int i = 0; i < 30; i++){
			fread(layerNameChar + i,sizeof(char),1,fp);
			if(layerNameChar[i] == '\n'){
				layerNameChar[i] = '\0';
				break;
			}
		}
		//读取线
		fscanf_s(fp,"%d",&hasPolyline);
		if(hasPolyline == 1){
			fscanf_s(fp,"%lf",&lineWidth);
			fscanf_s(fp,"%d,%d,%d",&r,&g,&b);
			polylineColor.r = r;
			polylineColor.g = g;
			polylineColor.b = b;
		}
		fscanf_s(fp,"%d",&hasPolygon);
		if(hasPolygon == 1){
			fscanf_s(fp,"%d,%d,%d",&r,&g,&b);
			polygonColor.r = r;
			polygonColor.g = g;
			polygonColor.b = b;
		}
		//读取完毕，进行封装
		pro->layerName = new CString(layerNameChar);
		pro->hasPolyline = hasPolyline;
		if(hasPolyline == 1){
			pro->lineWidth = lineWidth;
			pro->polylineColor = polylineColor;
		}
		pro->hasPolygon = hasPolygon;
		if(hasPolygon == 1){
			pro->polygonColor = polygonColor;
		}

		pros[10];
	}
}


void CMyMFC1View::addProsData(){
	int layerNum = map->getLayerNum();
	//每一图层
	for(int i = 0; i <layerNum;i++){
		//每一配置
		for(int j = 0; j < layerNum ; j++){
			//每一图层上的每个要素
			if(*pros[j].layerName == map->getLayerAt(i)->getName()){
				CGeoLayer* layer = map->getLayerAt(i);
				for(int k = 0; k < layer->getObjsNum(); k++){
					CGeoObject* obj = layer->getObjectAt(k);
					if(obj->getType() == 1 && pros[j].hasPolyline == 1){
						CGeoPolyline* polyline = (CGeoPolyline*)obj;
						polyline->setLineWidth(pros[j].lineWidth);
						polyline->setLineColor(pros[j].polylineColor.r,pros[j].polylineColor.g,pros[j].polylineColor.b);
					}
					if(obj->getType() == 2 && pros[j].hasPolygon == 1){
						CGeoPolygon* polygon = (CGeoPolygon*)obj;
						polygon->setLineColor(pros[j].polygonColor.r,pros[j].polygonColor.g,pros[j].polygonColor.b);
					}
					
				}
			}
		}
	}
}

void CMyMFC1View::readExcelData(char* pathChar)
{
	Excel excl;
	bool bInit = excl.initExcel();
	if(!excl.open(pathChar)){
		AfxMessageBox(_T("excel文件打开出错"));
	}
	CString strSheetName = excl.getSheetName(1);
	bool bLoad = excl.loadSheet(strSheetName);
	int nRow = excl.getRowCount();
	CString cityName;
	int x;
	int y;
	CGeoLayer* annoLayer = new CGeoLayer();
	this->map->addLayer(annoLayer);
	CGeoAnnotation* anno;
	for(int i = 2; i < nRow;i++){
		anno = new CGeoAnnotation();
		cityName = excl.getCellString(i,1);
		x = excl.getCellInt(i,2);
		y = excl.getCellInt(i,3);
		anno->setLocation(x,y);
		anno->setAnno(cityName);
		annoLayer->addObject(anno);
	}
}

void CMyMFC1View::readBLData(FILE* fp){
	char* line = new char[50];
	fgets(line,50,fp);
	fgets(line,50,fp);
	double left, right,top,bottom;
	for(int i = 0; i <5; i++ ){
		fscanf_s(fp, "%s",line,50);
	}
	fscanf_s(fp, " (%lf,%lf) (%lf,%lf)", &left, &bottom, &right, &top);
	CRect* blrect =  new CRect((int)(left*MULTI),(int)(top*MULTI),(int)(right*MULTI),(int)(bottom*MULTI));
	map->setRect(blrect);
	rect = blrect;
	for(int i = 0; i <19; i++){
		fscanf_s(fp, "%s",line,50);
	}
	//正式读取数据
	int ptsNum;
	double l,b;
	CGeoLayer* layer = new CGeoLayer;
	map->addLayer(layer);
	while(fscanf_s(fp, "%s",line,50) != EOF){
		if(strcmp(line,"PLINE") == 0){
			fscanf_s(fp, " %d",&ptsNum);
			CGeoPolyline* polyline = new CGeoPolyline;
			layer->addObject(polyline);
			for(int i = 0; i < ptsNum; i++){
				fscanf_s(fp, "%lf %lf",&l,&b);
				CPoint* pt = new CPoint((int)(l*MULTI),(int)(b*MULTI));
				polyline->addPoint(pt);
			}
		}else if(strcmp(line,"LINE") == 0){
			CGeoPolyline* polyline = new CGeoPolyline;
			layer->addObject(polyline);
			for(int i = 0; i < 2;i++){
				fscanf_s(fp, " %lf%lf",&l,&b);
				CPoint* pt = new CPoint((int)(l*MULTI),(int)(b*MULTI));
				polyline->addPoint(pt);
			}
		}
	}
}

//按下鼠标左键
void CMyMFC1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if(status == ZOOMIN){
		downPoint = point;
		upPoint = point;
		isPressed = true;
//	}

}


//抬起鼠标右键
void CMyMFC1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(map == NULL){
		return;
	}
	upPoint = point;
	CDC* pDC = GetDC();
	this->OnPrepareDC(pDC);
	CRect client;
	GetClientRect(&client);
	if(isPressed == false)
		{
			return;
		}
		if(downPoint.x == point.x ||downPoint.y == point.y){
			isPressed = false;
			return;
		}
	if(status == ZOOMIN || status == NO_ZOOMIN){
		//转换坐标
		pDC->DPtoLP(&upPoint);
		pDC->DPtoLP(&downPoint);
		CPoint delta = ProDelta(pDC,deltaAll);
		//rect记录的是真实逻辑坐标
		int l = downPoint.x < upPoint.x?downPoint.x:upPoint.x;
		int t = downPoint.y > upPoint.y?downPoint.y:upPoint.y;
		int r = downPoint.x > upPoint.x?downPoint.x:upPoint.x;
		int b = downPoint.y < upPoint.y?downPoint.y:upPoint.y;
		if(status == ZOOMIN){
			rect = CRect(l,t,r,b) - delta; // 确定onprepareddc中的窗口范围
			deltaAll = CPoint(0,0);
		}
		if(status == NO_ZOOMIN){
			CRect clipRect = CRect(l,t,r,b) + delta;
			if(map == NULL) return;
			map->clipRect = clipRect;
			for(int i = 0; i < map->getLayerNum(); i++){
				CGeoLayer* layer = map->getLayerAt(i);
				layer->clipRect = clipRect;
				for(int j = 0; j < layer->getObjsNum();j++){
					layer->getObjectAt(j)->clipRect = clipRect;
				}
			}
			map->clipMap(clipRect); //clip map中的各种对象
			deltaAll = CPoint(0,0);
		}
		Invalidate();
	}
	if(status == TRANSLATION){
		CPoint p1(downPoint);
		CPoint p2(upPoint);
		CPoint deltaP = p2 - p1;
		deltaAll += deltaP;
	}
	isPressed = false;
}


void CMyMFC1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	upPoint = point;
	if(isPressed == false){
			return;
		}
		if(downPoint.x == point.x ||downPoint.y == point.y){
			return;
		}
	CRect client;
	GetClientRect(&client);
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);
	if(status == ZOOMIN || status == NO_ZOOMIN){
		int oldRop = pDC->SetROP2(R2_NOTXORPEN);
		int l = downPoint.x > upPoint.x?downPoint.x:upPoint.x;
		int t = downPoint.y > upPoint.y?downPoint.y:upPoint.y;
		int r = downPoint.x < upPoint.x?downPoint.x:upPoint.x;
		int b = downPoint.y < upPoint.y?downPoint.y:upPoint.y;
		pDC->Rectangle(CRect(l,t,r,b));
		 l = downPoint.x < point.x?downPoint.x:point.x;
		 t = downPoint.y < point.y?downPoint.y:point.y;
		 r = downPoint.x > point.x?downPoint.x:point.x;
		 b = downPoint.y > point.y?downPoint.y:point.y;
		CRect boardRect = CRect(l,t,r,b);
		pDC->Rectangle(boardRect);
	}
	if(status == TRANSLATION){

		pDC->DPtoLP(client);
		CPoint p1(downPoint);
		CPoint p2(upPoint);
		CPoint deltaP = p2 - p1;
		deltaP = deltaP + deltaAll;
		CPoint dPPoint = deltaP;
		deltaP = ProDelta(pDC,deltaP);
		pDC->BitBlt(client.left,client.top,client.Width(),client.Height(),MemDC,client.left - deltaP.x,client.top - deltaP.y,SRCCOPY);
		//绘制空白区域
		if(dPPoint.x >0){
			pDC->FillSolidRect(client.left,client.top,deltaP.x,client.Height(),pDC->GetBkColor());
		}else{
			pDC->FillSolidRect(client.right + deltaP.x, client.top, -deltaP.x,client.Height(),pDC->GetBkColor());
		}
		if(dPPoint.y >0){
			pDC->FillSolidRect(client.left,client.top,client.Width(),deltaP.y,pDC->GetBkColor());
		}else{
			pDC->FillSolidRect(client.left, client.bottom + deltaP.y,client.Width(),-deltaP.y,pDC->GetBkColor());
		}
	}
}




//得到逻辑坐标下的偏移向量
CPoint CMyMFC1View::ProDelta(CDC* pDC, CPoint delta){
	CPoint zero(0,0);
	pDC->DPtoLP(&zero);
	pDC->DPtoLP(&delta);
	return (delta - zero);
}


void CMyMFC1View::OnButtonZoomin()
{
	// TODO: 在此添加命令处理程序代码
	if(map == NULL){
		return;
	}
	//缩放与非缩放模式互相切换
	if(status == NO_ZOOMIN){
		status = ZOOMIN;
	}else if (status == ZOOMIN){
		status = NO_ZOOMIN;
	}
	//如缩放与非缩放都不是，切换回缩放模式
	if(status != ZOOMIN && status != NO_ZOOMIN){
		status = ZOOMIN;
	}
	//更新info
	info->status = status;
}


void CMyMFC1View::OnButtonAll()
{
	// TODO: 在此添加命令处理程序代码
	if(map == NULL){
		return;
	}
	if(map->getRect() == this->rect && deltaAll == CPoint(0,0)){
		return;
	}
	if(map->getRect() != this->rect){
		deltaAll = CPoint(0,0);
		rect = map->getRect();
		Invalidate();
		return;
	}
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);
	if(deltaAll != CPoint(0,0)){
		deltaAll = CPoint(0,0);
		OnDraw(pDC);
	}
}

int isClockWise(CGeoPolygon* po){
	//遍历出最右侧的三个点
	int index = 0;
	int xMax = po->getPointAt(0)->x;
	int temp;
	for(int i = 0; i < po->getSize()-1;i++){
		temp = po->getPointAt(i+1)->x;
		if(temp>xMax){
			xMax = temp;
			index = i+1;
		}
		if(i == po->getSize() - 1){
			temp = po->getPointAt(0)->x;
			if(temp>xMax){
				xMax = temp;
				index = 0;
			}
		}
	}
	//求外积
	CPoint* a,*b,*c;
	int ia,ib,ic;
	if(index >  0 && index < po->getSize() -1 ){
		ia = index -1;
		ib = index;
		ic = index +1;
	}
	if(index == 0){
		ia = po->getSize()-1;
	}
	if(index == po->getSize() -1){
		ic = 0;
	}
	a = po->getPointAt(ia);
	b = po->getPointAt(ib);
	c = po->getPointAt(ic);
	int rlt = (b->x - a->x)*(c->y-b->y)-(c->x-b->x)*(b->y-a->y);
	if(rlt > 0){
		return 0;	
	}else{
		return 1;
	}
}

//假定向量p0p1是从下到上穿越的
int isLeft(CPoint p0, CPoint p1, CPoint p2){
	int result = (p1.x - p0.x)*(p1.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
	if(result > 0){
		return 1;
	}else{
		return 0;
	}
}

//得到出多边形的envelope
CRect getEnvelope(CPoint* points, int n){
	int top = 0,right = 0, bottom = 0, left = 0;
	for(int i = 0; i < n - 1; i++){
		if(points[i].y > points[top].y){
			top = i;
		}
		if(points[i].y < points[bottom].y){
			bottom = i;
		}
		if(points[i].x > points[right].x){
			right = i;
		}
		if(points[i].x > points[top].x){
			left = i;
		}
	}
	return CRect(points[left].x,points[top].y,points[right].x,points[bottom].y);
}

int wn_Pnpoly(CPoint p, CPoint*v, int n){
	int wn = 0;
	CRect enve = getEnvelope(v, n);
	if(p.x < enve.left || p.x > enve.right || p.y > enve.top || p.y < enve.bottom){
		return 0;
	}
	for(int i=0; i < n ; i++){
		//判断是被夹在中间
		if(v[i].y < p.y && v[i+1].y < p.y || v[i].y > p.y && v[i+1].y > p.y){
			continue;
		}
		if(v[i].y < p.y){
			if(isLeft(v[i], v[i+1], p) == 1){
				wn++;
			}
		}
		if(v[i].y > p.y){
			if(isLeft(v[i-1], v[i], p) == 1){
				wn--;
			}
		}
	}
	return wn;
}



CPoint getInnerPoint(CPoint* v, int n){
	CRect enve = getEnvelope(v, n);
	int m = 2;
	while(true){
		CPoint p = CPoint((enve.top + enve.bottom)/m, (enve.left + enve.right)/m);
		if(wn_Pnpoly(p, v, n) > 0 ){
			return p;	
		}
		p.x = enve.left - (enve.right - enve.left)/20;
		int d;
		int count = 0;
		int rightMost = 0, rightSecond = 0; 
		for (int i = 0, j = n-1; i < n; j = i++) 
		{
			if ( ((v[i].y>p.y) != (v[j].y>p.y))){
				if(v[j].y-v[i].y == 0){
					m++;
					continue;
				}
				d = p.x < (v[j].x-v[i].x) * (p.y-v[i].y) / (v[j].y-v[i].y) + v[i].x - p.x;
				if(d > 0){
					if(d > rightMost){
						rightSecond = rightMost;
						rightMost = d;
					}
				}
				count++;
			}
		}
		CPoint target = CPoint((rightMost + rightSecond)/2 + p.x, p.y);
		if(wn_Pnpoly(target, v, n) > 0 ){
			return target;	
		}
		m++;
	}
}


BOOL CMyMFC1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
}


void CMyMFC1View::OnButtonTranslation()
{
	// TODO: 在此添加命令处理程序代码
	status = TRANSLATION;
	info->status = status;
}


void CMyMFC1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(map == NULL){
		return;
	}
	CRect client;
	GetClientRect(&client);
	CDC* pDC = GetDC();
	MemBitmap.DeleteObject();
	MemBitmap.CreateCompatibleBitmap(pDC,client.Width(),client.Height());
	MemDC->SelectObject(MemBitmap);
}
