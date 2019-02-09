#include "stdafx.h"
#include "hpBar.h"

C_BAR::C_BAR():
	_fLeft(0.0f),
	_fTop(0.0f),
	_strBack(""),
	_strFront(""),
	_fLastPixel(0),
	_byteAlpha(0),
	_fStartPoxel(0)
{
}

C_BAR::~C_BAR()
{
}

HRESULT C_BAR::init()
{
	_strBack = "hpBarBack";
	_strFront = "HpBarFront";
	_fLastPixel = 103;
	_fStartPoxel = 500 - 26;
	_fLeft = 50.0f;
	_fTop = 10.0f;
	_byteAlpha = 0xf0;
	_bIsDraw = true;
	_bISSingle = false;
	return S_OK;
}

void C_BAR::release()
{
	_bIsDraw = false;

}

void C_BAR::update()
{
	

}

void C_BAR::render()
{
	if (_bIsDraw )
	{
		if (!_bISSingle)
		{
			IMAGEMANAGER->render(_strBack, getMemDC(), _fLeft, _fTop);
			IMAGEMANAGER->render(_strFront, getMemDC(), _fLeft, _fTop, 0, 0, (int)_fStartPoxel, 30);

		}
		else {
			IMAGEMANAGER->render(_strFront, getMemDC(), _fLeft, _fTop, 0, 0, (int)_fStartPoxel, 10);

		}
	}
}


void C_BAR::setImg(string strFront)
{
	_strFront = strFront;
	_fLastPixel = 0;
}

void C_BAR::setNomalizeDamage(int nHp)
{
	int	nWidth = _fStartPoxel - _fLastPixel;
	_fNomalizeDamage = (float)nWidth / (float)nHp;
}
