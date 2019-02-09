#include "stdafx.h"
#include "score.h"

C_SCORE::C_SCORE()
{
}

C_SCORE::~C_SCORE()
{
}

void C_SCORE::create(float fPosX, float fPosY, E_ITEMTYPE eItemType)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_pImg = IMAGEMANAGER->findImage("score");
	_nWidth = _pImg->GetWidth();
	_nHeight = _pImg->GetHeight();
	_nPoint = 1000;
	_eItem = eItemType;
	_fAngle = PI / 2.0f;
	_fSPeedY = 3.0f;

}

void C_SCORE::render(HDC hdc)
{
	_pImg->renderCenter(hdc, _fPosX, _fPosY);

}

void C_SCORE::release()
{
	_fPosX = -2000;
	_fPosY = -2000;

	_pImg = nullptr;
}

void C_SCORE::update()
{
	_fPosX += Mins::presentPowerX(_fAngle, _fSpeedX);
	_fPosY += Mins::presentPowerY(_fAngle, _fSPeedY);
	if (_fAngle < PI + PI / 2.0f)
	{
		_fAngle += 0.2f;

	}
}

I_ITEM::E_ITEMTYPE C_SCORE::getItemType()
{
	return _eItem;
}

int C_SCORE::getPoint()
{
	return _nPoint;
}

float C_SCORE::getPosX()
{
	return _fPosX;
}

float C_SCORE::getPosY()
{
	return _fPosY;
}

float C_SCORE::getWidth()
{
	return _nWidth;
}

float C_SCORE::getHeight()
{
	return _nHeight;
}

void C_SCORE::init()
{
	_fPosX = -2000;
	_fPosY = -2000;
	_pImg = nullptr;
	_nWidth = 0;
	_nHeight = 0;
	_nPoint = 0;
	_eItem = I_ITEM::E_ITEMTYPE::E_MAX;
	_fAngle = 0.0f;
	_fSpeedX=0.0f;
	_fSPeedY = 3.0f;
}

void C_SCORE::setDrain(int fPosX, int fPosY)
{
	_fAngle = getAngle(_fPosX, _fPosY, fPosX, fPosY);
	_fAngle += PI2;
	_fSpeedX = 10.0f;
	_fSPeedY = 10.0f;
	
}
