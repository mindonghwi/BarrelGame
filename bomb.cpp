#include "stdafx.h"
#include "bomb.h"

C_BOMB::C_BOMB()
{
}

C_BOMB::~C_BOMB()
{
}

void C_BOMB::create(float fPosX, float fPosY, E_ITEMTYPE eItemType)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_pImg = IMAGEMANAGER->findImage("bomb");
	_nWidth = _pImg->GetWidth();
	_nHeight = _pImg->GetHeight();
	_nPoint = 1;
	_eItem = eItemType;
	_fAngle = PI / 2.0f;
	_fSPeedY = 3.0f;

}

void C_BOMB::render(HDC hdc)
{
	_pImg->renderCenter(hdc, (int)_fPosX, (int)_fPosY);
}

void C_BOMB::release()
{
	_fPosX = -2000;
	_fPosY = -2000;

	_pImg = nullptr;
}

void C_BOMB::update()
{
	_fPosX += Mins::presentPowerX(_fAngle, _fSpeedX);
	_fPosY += Mins::presentPowerY(_fAngle, _fSPeedY);
	if (_fAngle < PI + PI / 2.0f)
	{
		_fAngle += 0.2f;
	}
}

I_ITEM::E_ITEMTYPE C_BOMB::getItemType()
{
	return _eItem;
}

int C_BOMB::getPoint()
{
	return _nPoint;
}

float C_BOMB::getPosX()
{
	return _fPosX;
}

float C_BOMB::getPosY()
{
	return _fPosY;
}

float C_BOMB::getWidth()
{
	return (float)_nWidth;
}

float C_BOMB::getHeight()
{
	return (float)_nHeight;
}

void C_BOMB::init()
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

void C_BOMB::setDrain(int fPosX, int fPosY)
{
	_fAngle = getAngle( _fPosX, _fPosY, (float)fPosX, (float)fPosY);
	_fAngle += PI2;
	_fSpeedX = 10.0f;
	_fSPeedY = 10.0f;
}

