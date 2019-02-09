#include "stdafx.h"
#include "effect.h"

C_EFFECT::C_EFFECT() :
	_fPosX(0.0f),
	_fPosY(0.0f),
	_pImg(nullptr),
	_strImageKey(""),
	_nCurrentFrameX(0),
	_nMaxFrame(0),
	_bIsRemove(false),
	_nFrameCount(0),
	_byteAlphaRander(0xff),
	_nWidth(0),
	_nHeight(0)
{
}

C_EFFECT::~C_EFFECT()
{
}


void C_EFFECT::init(float fPosX, float fPosY)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_strImageKey = "";
	_pImg = nullptr;
	_nMaxFrame = 0;
	_nCurrentFrameX = 0;
	_bIsRemove = false;
	_nFrameCount = 0;
	_byteAlphaRander = 0x00;
	_nWidth = 0;
	_nHeight = 0;
}

void C_EFFECT::release()
{
	_pImg = nullptr;
}

void C_EFFECT::update()
{
	_nFrameCount++;

	if (_nFrameCount > 5)
	{
		_nCurrentFrameX++;

			if (_nCurrentFrameX >= _nMaxFrame)
			{

				if (_strImageKey != "enemyEffectDeath" && _nCurrentFrameX >= _nMaxFrame)
				{
					_bIsRemove = true;
				}

				_nCurrentFrameX = _nMaxFrame - 1;
				_byteAlphaRander -= 25;
				if (_byteAlphaRander < 10)
				{
					_bIsRemove = true;
				}
			}
		
		_nFrameCount = 0;
	}
}

void C_EFFECT::render()
{
	_pImg->alphaFrameRender(getMemDC(), _fPosX - _nWidth/2, _fPosY - _nHeight/2, _nCurrentFrameX, 0, _byteAlphaRander);
}

void C_EFFECT::create(float fPosX, float fPosY, const char * str)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_strImageKey = str;
	_pImg = IMAGEMANAGER->findImage(_strImageKey);
	_nMaxFrame = _pImg->getMaxFrameX();
	_nCurrentFrameX = 0;
	_bIsRemove = false;
	_nFrameCount = 0;
	_byteAlphaRander = 0xff;
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();
}

void C_EFFECT::destroy()
{
	_fPosX = -2000;
	_fPosY = -2000;
	_strImageKey = "";
	_pImg = nullptr;
	_nMaxFrame = 0;
	_nCurrentFrameX = 0;
	_bIsRemove = false;
	_nFrameCount = 0;
	_byteAlphaRander = 0x00;
	_nWidth = 0;
	_nHeight = 0;
}
