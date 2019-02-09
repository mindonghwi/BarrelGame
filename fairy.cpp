#include "stdafx.h"
#include "fairy.h"

C_FAIRY::C_FAIRY()
{
}

C_FAIRY::~C_FAIRY()
{
}

void C_FAIRY::create(float fPosX, float fPosY, float fAngle, float fSpeed)
{
	//생성할때 
	_fAngle = fAngle;
	_fPosX = fPosX;
	_fPosY = fPosY;
	_fSpeed = fSpeed;
	_pImg = IMAGEMANAGER->findImage("fairy");
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();
	_nCurrentFrameX = 0;
	_nCurrentFrameY = 0;
	_eAniStatus = C_FAIRY::E_ANIMATION::E_IDLE;
	_bIsRemove = false;
	_fMovingChanging = 150.0f;
	_bIsPanelOn = false;
	_nAniMationFrame = 0;
	_nDeathCount = 0;
	for (int i = 0; i < static_cast<int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX); i++)
	{
		_arFireTimer[i] = 0;
		_arIsFiring[i] = false;
	}

	
	_arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_LOW)] = 200;
	_arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_HIGH)] = 600;
	_arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_LOW)] = 50;
	_arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_HIGH)] = 250;
	

	_nHp = 1000;

	setSpiral();
}

void C_FAIRY::update()
{
	//사선으로 움직여서 y축이 100인 지점에 도착하면 멈추고 공격을 시작한다.
	if (_fPosY < _fMovingChanging)
	{
		_fPosX += Mins::presentPowerX(_fAngle, _fSpeed);
		_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);
	}
	else
	{
		if (!_bIsPanelOn)
		{
			setPanel();
		}
		_bIsPanelOn = true;
	}


	for (int i = static_cast<int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL); i < static_cast<int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX); i++)
	{
		if (_bIsPanelOn)
		{
			_arFireTimer[i]++;

		}
	}

	if (_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] > _arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_LOW)]
		&& _arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] < _arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_HIGH)]
		)
	{
		if (_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] % 20 == 0)
		{
			_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] = true;
		}
	}
	else
	{
		if (_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] == _arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_HIGH)])
		{
			_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] = 0;
		}
		_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)] = false;
	}

	if (_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] > _arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_LOW)]
		&& _arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] < _arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_HIGH)])
	{
		if (_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] % 3 == 0)
		{
			_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] = true;
		}
		else {
			_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] = false;

		}
	}
	else
	{
		if (_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] == _arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_HIGH)])
		{
			_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] = 0;
		}
		_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)] = false;
	}

	moveSpiral();

	if (!_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)])
	{
		movePanel();
	}


	_nAniMationFrame++;
	if (_nAniMationFrame % 5 == 0)
	{
		_nCurrentFrameX++;
		if (_nCurrentFrameX > 4)
		{
			_nCurrentFrameX = 0;
		}
		_nAniMationFrame = 0;
	}

	_nDeathCount++;
	if (_nDeathCount % 700 == 0 )
	{
		_bIsRemove = true;
	}
}

void C_FAIRY::release()
{
	_pImg = nullptr;
}

void C_FAIRY::render(HDC hDc)
{
	_pImg->frameRenderCenter(hDc, static_cast<int>(_fPosX), static_cast<int>(_fPosY), _nCurrentFrameX, static_cast<int>(_eAniStatus));
	renderPanel(hDc);
}

void C_FAIRY::fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{
	if (_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_PANEL)])
	{
		float fAngle = 0.0f;
		for (int i = 0; i < 4; i++)
		{
			pBulletMgr->fire(_arPanelPosX[i], _arPanelPosY[i], fAngle, 0.0f, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
			fAngle += PI / 2.0f;
		}
	}

	if (_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_SPIRAL)])
	{
		for (int i = 0; i < 4; i++)
		{
			//pBulletMgr->fire(_arSpiralBulletPosX[i], _arSpiralBulletPosY[i], _arSpiralBulletAngle[i], 0, IMAGEMANAGER->findImage("SBullet"), 6.0f, 20, 20, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
			pBulletMgr->fire(_fPosX, _fPosY, _arSpiralBulletAngle[i],0.0f, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
			pBulletMgr->setFrameY(i);
		}
	}

}

bool C_FAIRY::checkRemove()
{
	return _bIsRemove;
}

bool C_FAIRY::checkFireOk()
{
	return true;
}

float C_FAIRY::getPosX()
{
	return _fPosX;
}

float C_FAIRY::getPosY()
{
	return _fPosY;
}

int C_FAIRY::getRadius()
{
	return _nWidth;
}

void C_FAIRY::setPanel()
{
	//판넬 초기화
	float fPos = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		_arPanelPosX[i] = _fPosX + Mins::presentPowerX(fPos, 40);
		_arPanelPosY[i] = _fPosY + Mins::presentPowerY(fPos, 40);
		_arPanelAngle[i] = fPos;
		fPos += PI / 2.0f;
	}

	_pPanelImg = IMAGEMANAGER->findImage("magicPanel");
	_nPanelCurrentFrameX = 0;
}

void C_FAIRY::renderPanel(HDC hDc)
{
	//그리기 시작하면 그려라
	if (_bIsPanelOn)
	{
		for (int i = 0; i < 4; i++)
		{
			_pPanelImg->frameRenderCenter(hDc, _arPanelPosX[i], _arPanelPosY[i], _nPanelCurrentFrameX, 0);
		}
	}
}

void C_FAIRY::movePanel()
{
	if (_bIsPanelOn)
	{
		//애니메이션 설정
		_nPanelCurrentFrameX++;
		if (_nPanelCurrentFrameX >= 8)
		{
			_nPanelCurrentFrameX = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			_arPanelAngle[i] += 0.2f;

			_arPanelPosX[i] = _fPosX + Mins::presentPowerX(_arPanelAngle[i], 40.0f);
			_arPanelPosY[i] = _fPosY + Mins::presentPowerY(_arPanelAngle[i], 40.0f);
		}
	}
}

void C_FAIRY::setSpiral()
{
	float fPos = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		_arSpiralBulletAngle[i] = fPos;
		fPos += PI / 2.0f;
	}
}

void C_FAIRY::moveSpiral()
{
	for (int i = 0; i < 4; i++)
	{
		_arSpiralBulletAngle[i] += 0.2f;

		if (_arSpiralBulletAngle[i] > PI2)
		{
			_arSpiralBulletAngle[i] = _arSpiralBulletAngle[i] - PI2;
		}

	}
}

void C_FAIRY::damage(int nDamage)
{
	_nHp -= nDamage;

	if (_nHp <= 0)
	{
		_bIsRemove = true;
	}
}

int C_FAIRY::getHp()
{
	return _nHp;
}

int C_FAIRY::getItem()
{
	return 1;
}

bool C_FAIRY::bulletClear()
{
	return false;
}
