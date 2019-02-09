#include "stdafx.h"
#include "flora.h"

//맴버 변수 이니셜라이징
C_FLORA::C_FLORA():
	_fAngle(0.0f),
	_fPosX(0.0f),
	_fPosY(0.0f),
	_nWidth(0),
	_nHeight(0),
	_fSpeed(0),
	_pImg(nullptr),
	_nCurrentFrameX(0),
	_nCurrentFrameY(0),
	_bIsRemove(false),
	_nBulletReload(0),
	_bIsFire(false)
{
}

C_FLORA::~C_FLORA()
{
}

void C_FLORA::create(float fPosX, float fPosY, float fAngle, float fSpeed)
{
	//생성할때 
	_fAngle = fAngle;
	_fPosX = fPosX;
	_fPosY = fPosY;
	_fSpeed = fSpeed;
	_pImg = IMAGEMANAGER->findImage("flora");
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();
	_nCurrentFrameX	= 0;
	_nCurrentFrameY	= 0;
	_eAni = C_FLORA::E_ANI::E_IDLE;
	_bIsRemove = false;
	_nBulletReload = 10;
	_bIsFire = true;
	_nHp = 10;
	_pEffectImage = IMAGEMANAGER->findImage("effectRainBow");
	_nEffectFrameX = 0;
}

void C_FLORA::update()
{
	//이동
	_fPosX += Mins::presentPowerX(_fAngle, _fSpeed);
	_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);

	
	//퇴장
	//상승하고 있다
	if (_fAngle < PI)
	{
		if (_fPosY + _nHeight / 2 < 0)
		{
			_bIsRemove = true;
		}
	}
	//하강중
	if (_fAngle < PI2 && _fAngle > PI)
	{
		if (_fPosY - _nHeight / 2 > WINSIZEY)
		{
			_bIsRemove = true;
		}
	}
	//우로
	if (_fAngle < PI / 2)
	{
		//우측
		if (_fPosX - _nWidth / 2 > WINSIZEX)
		{
			_bIsRemove = true;
		}
	}
	//좌로
	if (_fAngle > PI / 2)
	{
		//좌측
		if (_fPosX + _nWidth / 2 < 0)
		{
			_bIsRemove = true;
		}
	}


	//애니메이션 상태 체크
	if (fabsf( _fAngle-PI/2) < FLT_EPSILON || fabsf(_fAngle - (PI / 2 + PI)) < FLT_EPSILON)
	{
		_eAni = C_FLORA::E_ANI::E_IDLE;
		_nCurrentFrameY = 0;
			}
	else if (_fAngle > PI / 2 || _fAngle <(PI / 2 + PI))
	{
		_eAni = C_FLORA::E_ANI::E_LEFT;
		_nCurrentFrameY = 1;
	}
	else if (_fAngle < PI / 2 || _fAngle >(PI / 2 + PI))
	{
		_eAni = C_FLORA::E_ANI::E_RIGHT;
		_nCurrentFrameY = 2;
	}

	//애니메이션 갱신
	_nAniMationFrame++;
	if (_nAniMationFrame % 10 == 0)
	{
		_nAniMationFrame = 0;
		if (_eAni == C_FLORA::E_ANI::E_IDLE)
		{
			_nCurrentFrameX++;
			if (_nCurrentFrameX > 4)
			{
				_nCurrentFrameX = 0;
			}
			
		}
		else if (_eAni = C_FLORA::E_ANI::E_LEFT)
		{
			_nCurrentFrameX++;
			if (_nCurrentFrameX > 6)
			{
				_nCurrentFrameX = 0;
			}
		}
		else if (_eAni = C_FLORA::E_ANI::E_RIGHT)
		{
			_nCurrentFrameX--;
			if (_nCurrentFrameX < 0)
			{
				_nCurrentFrameX = 6;
			}
		}

		_nEffectFrameX++;
		if (_nEffectFrameX >= _pEffectImage->getMaxFrameX())
		{
			_nEffectFrameX = 0;
		}
	}



	_nBulletReload++;

	if (_nBulletReload == 10)
	{
		_bIsFire = true;
	}



}

void C_FLORA::release()
{
	_pImg = nullptr;
}

void C_FLORA::render(HDC hDc)
{
	_pEffectImage->frameRenderCenter(hDc, static_cast<int>(_fPosX), static_cast<int>(_fPosY), _nEffectFrameX, 0);
	_pImg->frameRenderCenter(hDc,static_cast<int>(_fPosX), static_cast<int>(_fPosY), _nCurrentFrameX, _nCurrentFrameY);
}

void C_FLORA::fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{
	if (_fAngle < PI && _fPosY < 100)
	{
		pBulletMgr->fire(_fPosX, _fPosY, getAngle(_fPosX, _fPosY, pPlayer->getPosX(), pPlayer->getPosY()), 0.0f, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);

	}
	else if (_fAngle > PI && _fPosY > WINSIZEY / 2)
	{
		pBulletMgr->fire(_fPosX, _fPosY, getAngle(_fPosX, _fPosY, pPlayer->getPosX(), pPlayer->getPosY()), 0.0f, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
	}
	_nBulletReload = 1;
	_bIsFire = false;
}

bool C_FLORA::checkRemove()
{
	return _bIsRemove;
}

bool C_FLORA::checkFireOk()
{
	return _bIsFire;
}

float C_FLORA::getPosX()
{
	return _fPosX;
}

float C_FLORA::getPosY()
{
	return _fPosY;
}

int C_FLORA::getRadius()
{
	return _nWidth;
}

void C_FLORA::damage(int nDamage)
{
	_nHp -= nDamage;

	if (_nHp <= 0)
	{
		_bIsRemove = true;
	}
}

int C_FLORA::getHp()
{
	return _nHp;
}

int C_FLORA::getItem()
{
	return 0;
}

bool C_FLORA::bulletClear()
{
	return false;
}

