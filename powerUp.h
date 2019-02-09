#pragma once

#include "item.h"


class C_POWERUP : public I_ITEM {
private:
	int					_nPoint;
	float				_fPosX;
	float				_fPosY;
	int					_nWidth;
	int					_nHeight;
	image*				_pImg;
	I_ITEM::E_ITEMTYPE	_eItem;
	float				_fAngle;
	float				_fSpeedX;
	float				_fSPeedY;
public:
	C_POWERUP();
	~C_POWERUP();

	virtual void		create(float fPosX, float fPosY, E_ITEMTYPE eItemType)		override;
	virtual void		render(HDC hdc)												override;
	virtual void		release()													override;
	virtual void		update()													override;

	virtual I_ITEM::E_ITEMTYPE	getItemType()												override;
	virtual	int			getPoint()													override;

	virtual	float		getPosX()													override;
	virtual	float		getPosY()													override;
	virtual	float		getWidth()													override;
	virtual	float		getHeight()													override;
	virtual void		init()														override;
	virtual void		setDrain(int fPosX, int fPosY)								override;



private:
	const C_POWERUP& operator=(const C_POWERUP&);
	C_POWERUP(const C_POWERUP&);
};