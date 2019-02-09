#include "stdafx.h"
#include "powerUp.h"

C_POWERUP::C_POWERUP() :
	_nPoint(0),
	_fPosX(0.0f),
	_fPosY(0.0f),
	_nWidth(0),
	_nHeight(0),
	_pImg(),
	_eItem(I_ITEM::E_ITEMTYPE::E_MAX)
{
}

C_POWERUP::~C_POWERUP()
{
}

void C_POWERUP::create(float fPosX, float fPosY, E_ITEMTYPE eItemType)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_pImg = IMAGEMANAGER->findImage("power");
	_nWidth = _pImg->GetWidth();
	_nHeight = _pImg->GetHeight();
	_nPoint = 1;
	_eItem = eItemType;
	_fAngle = PI / 2.0f;
	_fSPeedY = 3.0f;

}

void C_POWERUP::render(HDC hdc)
{
	_pImg->renderCenter(hdc, _fPosX, _fPosY);
}

void C_POWERUP::release()
{
	_fPosX = -2000;
	_fPosY = -2000;

	_pImg = nullptr;
}

void C_POWERUP::update()
{
	_fPosX += Mins::presentPowerX(_fAngle, _fSpeedX);
	_fPosY += Mins::presentPowerY(_fAngle, _fSPeedY);
	if (_fAngle < PI + PI / 2.0f)
	{
		_fAngle += 0.2f;

	}
}

I_ITEM::E_ITEMTYPE C_POWERUP::getItemType()
{
	return _eItem;
}

int C_POWERUP::getPoint()
{
	return _nPoint;
}

float C_POWERUP::getPosX()
{
	return _fPosX;
}

float C_POWERUP::getPosY()
{
	return _fPosY;
}

float C_POWERUP::getWidth()
{
	return _nWidth;
}

float C_POWERUP::getHeight()
{
	return _nHeight;
}

void C_POWERUP::init()
{
	_fPosX = -2000;
	_fPosY = -2000;
	_pImg = nullptr;
	_nWidth = 0;
	_nHeight = 0;
	_nPoint = 0;
	_eItem = I_ITEM::E_ITEMTYPE::E_MAX;
	_fAngle = 0.0f;
	_fSpeedX = 0.0f;
	_fSPeedY = 3.0f;
}

void C_POWERUP::setDrain(int fPosX, int fPosY)
{
	_fAngle = getAngle(_fPosX, _fPosY, fPosX, fPosY);
	_fAngle += PI2;
	_fSpeedX = 10.0f;
	_fSPeedY = 10.0f;
}
