#include "stdafx.h"
#include "GeoObject.h"


CGeoObject::CGeoObject(void)
{
	wcRect = new CRect();
	name = *(new CString());
}


CGeoObject::~CGeoObject(void)
{
	if(wcRect != NULL)
		delete this->wcRect;
}

	void CGeoObject::setName(CString name){
		this->name = name;
	}
	CString CGeoObject::getName() const
	{
		return name;
	}
	void CGeoObject::setId(int id)
	{
		this->id = id;
	}
	int CGeoObject::getId() const
	{
		return id;
	}
	void CGeoObject::setRect(CRect* rect)
	{
		this->wcRect = rect;
	}
	void CGeoObject::setRect(int x1,int x2,int width,int height)
	{
		 wcRect->SetRect(x1,x2,x1+width,x2+height);
	}
	CRect* CGeoObject::getRect () const
	{
		return wcRect;
	}

	int CGeoObject::getCode(CRect wcRect, CPoint pt){
		int x = pt.x;
		int y = pt.y;
		int code = 0;
		if(pt.x < wcRect.left){
			code += 1;
		}
		if(pt.x > wcRect.right){
			code += 2;
		}
		if(pt.y > wcRect.top){
			code += 4;
		}
		if(pt.y < wcRect.bottom){
			code += 8;
		} 
		return code;
}

	CPoint* CGeoObject::getCrossRectPoint(CPoint st, CPoint en, CRect rect){
		int stCode = getCode(rect,st);
		int enCode = getCode(rect,en);
		CPoint in;
		CPoint out;
		int target;
		int k,y,x;
		if(stCode == 0){
			in = st;
			out = en;
			target = enCode;
		}
		if(enCode == 0){
			out = st;
			in = en;
			target = stCode;
		}
		if(target == LEFT){
			if(in.y = out.y){
				return new CPoint(rect.left,in.y);
			}
			k = (in.y - out.y)/(in.x - out.x);
			y = in.y - k*(in.x - rect.left);
			if(y >= rect.bottom && y < rect.top){
				return new CPoint(rect.left,y);
			}else if(y > rect.top){
				k = (in.x - out.x)/(in.y - out.y);
				x = out.x - k*(out.y - rect.top);
				return new CPoint(x,rect.top);
			}else if(y < rect.bottom){
				k = (in.x - out.x)/(in.y - out.y);
				x = out.x - k*(out.y - rect.bottom);
				return new CPoint(x,rect.bottom);
			}
		}else if (target == RIGHT){
			if(in.y = out.y){
				return new CPoint(rect.right,in.y);
			}
			k = (in.y - out.y)/(in.x - out.x);
			y = in.y - k*(in.x - rect.right);
			if(y >= rect.bottom && y < rect.top){
				return new CPoint(rect.right,y);
			}else if(y > rect.top){
				k = (in.x - out.x)/(in.y - out.y);
				x = out.x - k*(out.y - rect.top);
				return new CPoint(x,rect.top);
			}else if(y < rect.bottom){
				k = (in.x - out.x)/(in.y - out.y);
				x = out.x - k*(out.y - rect.bottom);
				return new CPoint(x,rect.bottom);
			}
		}else if(target == TOP){
			if(in.x = out.x){
				return new CPoint(in.x,rect.top);
			}
			k = (in.x - out.x)/(in.y - out.y);
			x = out.x - k*(out.y - rect.top);
			return new CPoint(x,rect.top);
		}else if(target == BOTTOM){
			if(in.x = out.x){
				return new CPoint(in.x,rect.bottom);
			}
			k = (in.x - out.x)/(in.y - out.y);
			x = out.x - k*(out.y - rect.bottom);
			return new CPoint(x,rect.bottom);
		}
	}

	CArray<CPoint*,CPoint*>* CGeoObject::getCrossRectPointTh(CPoint st, CPoint en, CRect rect){
		int stCode = getCode(rect,st);
		int enCode = getCode(rect,en);
		CPoint in;
		CPoint out;
		int target;
		int k,y,x;
		in = st;
		out = en;
		target = enCode;
		CArray<CPoint*,CPoint*>* result = new CArray<CPoint*,CPoint*>;
		for(int i = 0; i < 2;i++){
			if(target == LEFT){
				if(in.y = out.y){
					result->Add(new CPoint(rect.left,in.y));
				}
				k = (in.y - out.y)/(in.x - out.x);
				y = in.y - k*(in.x - rect.left);
				if(y >= rect.bottom && y < rect.top){
					result->Add(new CPoint(rect.left,y));
				}else if(y > rect.top){
					k = (in.x - out.x)/(in.y - out.y);
					x = out.x - k*(out.y - rect.top);
					if(x > rect.left && x < rect.right){
						result->Add(new CPoint(x,rect.top));
					}else{
						return result;
					}
				}else if(y < rect.bottom){
					k = (in.x - out.x)/(in.y - out.y);
					x = out.x - k*(out.y - rect.bottom);
					if(x > rect.left && x < rect.right){
						result->Add(new CPoint(x,rect.bottom));
					}else{
						return result;
					}
				}
			}else if (target == RIGHT){
				if(in.y = out.y){
					result->Add(new CPoint(rect.right,in.y));
				}
				k = (in.y - out.y)/(in.x - out.x);
				y = in.y - k*(in.x - rect.right);
				if(y >= rect.bottom && y < rect.top){
					result->Add(new CPoint(rect.right,y));
				}else if(y > rect.top){
					k = (in.x - out.x)/(in.y - out.y);
					x = out.x - k*(out.y - rect.top);
					if(x > rect.left && x < rect.right){
						result->Add(new CPoint(x,rect.top));
					}else{
						return result;
					}
				}else if(y < rect.bottom){
					k = (in.x - out.x)/(in.y - out.y);
					x = out.x - k*(out.y - rect.bottom);
					if(x > rect.left && x < rect.right){
						result->Add(new CPoint(x,rect.bottom));
					}else{
						return result;
					}
				}
			}else if(target == TOP){
				if(in.x = out.x){
					result->Add(new CPoint(in.x,rect.top));
				}
				k = (in.x - out.x)/(in.y - out.y);
				x = out.x - k*(out.y - rect.top);
				if(x > rect.left && x < rect.right){
					result->Add(new CPoint(x,rect.top));
				}else{
					return result;
				}
				
			}else if(target == BOTTOM){
				if(in.x = out.x){
					result->Add(new CPoint(in.x,rect.bottom));
				}
				k = (in.x - out.x)/(in.y - out.y);
				x = out.x - k*(out.y - rect.bottom);
				if(x > rect.left && x < rect.right){
					result->Add(new CPoint(x,rect.bottom));
				}else{
					return result;
				}
			}
			in = en;
			out = st;
			target = stCode;
		}
		return result;
	}


	CRect* CGeoObject::getEnvelope(CArray<CPoint*,CPoint*>* pts)
	{
		//得到出多边形的envelope
		int n = pts->GetSize();
		int top = 0,right = 0, bottom = 0, left = 0;
		for(int i = 0; i < n - 1; i++){
			if(pts->GetAt(i)->y > pts->GetAt(top)->y){
				top = i;
			}
			if(pts->GetAt(i)->y < pts->GetAt(bottom)->y){
				bottom = i;
			}
			if(pts->GetAt(i)->x >pts->GetAt(right)->x){
				right = i;
			}
			if(pts->GetAt(i)->x < pts->GetAt(left)->x){
				left = i;
			}
		}
		return new CRect(pts->GetAt(left)->x,pts->GetAt(top)->y,pts->GetAt(right)->x,pts->GetAt(bottom)->y);
	}


	boolean CGeoObject::isOver(CRect ro, CRect rt)
	{
		boolean isover = false;
		if(getCode(rt, ro.TopLeft()) == 0 ||getCode(rt, CPoint(ro.right,ro.top)) == 0 ||getCode(rt, CPoint(ro.left,ro.bottom)) == 0 ||getCode(rt,ro.BottomRight()) == 0 ){
			isover = true;
		}
		return isover;
	}

	int CGeoObject::getDirction(int code){
		if(code & 0001 == 1){
			return LEFT;
		}else if(code & 0010 == 1){
			return RIGHT;
		}else if(code & 0100 == 1){
			return TOP;
		}else if(code & 1000 == 1){
			return BOTTOM;
		}
	}

