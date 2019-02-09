#pragma once
#include "stdafx.h"

class I_ITEM abstract {
public:
	enum class E_ITEMTYPE {
		E_POWER = 0,
		E_BOMB,
		E_SCORE,
		E_MAX
	};

public:
	virtual void				create(float fPosX,float fPosY,E_ITEMTYPE eItemType)		abstract;
	virtual void				render(HDC hdc)												abstract;
	virtual void				release()													abstract;
	virtual void				update()													abstract;

	virtual I_ITEM::E_ITEMTYPE	getItemType()												abstract;
	virtual	int					getPoint()													abstract;

	virtual	float				getPosX()													abstract;
	virtual	float				getPosY()													abstract;
	virtual	float				getWidth()													abstract;
	virtual	float				getHeight()													abstract;
	virtual void				init()														abstract;
	virtual void				setDrain(int fPosX,int fPosY)								abstract;
};