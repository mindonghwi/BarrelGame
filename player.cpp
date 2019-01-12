#include "stdafx.h"
#include "player.h"
#include "enemyMgr.h"
#include "effectMgr.h"
#include "hpBar.h"
#include "itemMgr.h"

C_PLAYER::C_PLAYER():
	_fAngle(0.0f),
	_fPosX(0.0f),
	_fPosY(0.0f),
	_nWidth(0),
	_nHeight(0),
	_nCollisionRadius(0),
	_pImg(nullptr),
	_fSpeed(0.0f),
	_nFrameCount(0),
	_ePlayerState(C_PLAYER::E_PLAYERSTATE::E_IDLE),
	_nFrameX(0),
	_nPower(0),
	_nBulletFrameCount(0),
	_arPowerNPosX{}
{
}

C_PLAYER::~C_PLAYER()
{
}

HRESULT C_PLAYER::init()
{
	_pImg = IMAGEMANAGER->addFrameImage("player", "image/player.bmp", 203, 129, 7, 3, true, Mins::getMazenta());
	//_pImg = IMAGEMANAGER->addFrameImage("player", "image/player.bmp", 203, 129, 7, 3, true, RGB(255, 0, 255));

	_fPosX = static_cast<float>(WINSIZEX / 2);
	_fPosY = static_cast<float>(WINSIZEY - WINSIZEY / 10);
	_fAngle = PI / 2.0f;
	_fSpeed = 5.0f;
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();

	_nCollisionRadius = 5;
	_nPower = 1;
	_nBulletFrameCount = 0;

	_arPowerNPosX[0] = 0;
	_nSpellCount = 7;


	initSpell();
	
	return S_OK;
}

void C_PLAYER::release()
{
	_pImg = nullptr;
	pImage->release();
	delete pImage;
	pImage = nullptr;
	_vScore.clear();
}

void C_PLAYER::update()
{
	//좌로 이동
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_nFrameX = 0;
		_ePlayerState = C_PLAYER::E_PLAYERSTATE::E_LEFTMOVE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_LEFTMOVE)
		{
			_fAngle = PI;
			if (_fPosX - _nWidth/2 > 0)
			{
				_fPosX += cosf(_fAngle) * _fSpeed;
			}
			_ePlayerState = C_PLAYER::E_PLAYERSTATE::E_LEFTMOVE;
		}
	}
	if(KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_LEFTMOVE)
		{
			_ePlayerState = C_PLAYER::E_PLAYERSTATE::E_IDLE;
			_nFrameX = 0;
		}
	}

	//우로 이동
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_nFrameX = 6;
		_ePlayerState = C_PLAYER::E_PLAYERSTATE::E_RIGHTMOVE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_RIGHTMOVE)
		{
			_fAngle = 0;
			if (_fPosX + _nWidth / 2 < WINSIZEX)
			{
				_fPosX += cosf(_fAngle) * _fSpeed;
			}
			_ePlayerState = C_PLAYER::E_PLAYERSTATE::E_RIGHTMOVE;
		}		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_RIGHTMOVE)
		{
			_ePlayerState = C_PLAYER::E_PLAYERSTATE::E_IDLE;
			_nFrameX = 0;
		}
	}

	//상승
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_fAngle = PI/ 2.0f;
		if (_fPosY - _nHeight/2 > 0)
		{
			_fPosY += -sinf(_fAngle) * _fSpeed;
		}
	}
	//하강
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_fAngle = PI + PI/2.0f;
		if (_fPosY + _nHeight / 2 < WINSIZEY) {
			_fPosY += -sinf(_fAngle) * _fSpeed;
		}
	}

	//총알 발사
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		//_pBulletMgr->fire(this->getPosX() - 2, this->getPosY() - 30, PI / 2, 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 5.1f, 12, 12, 1, true, C_BULLET::E_BULLETTYPE::E_SPELL);
		//_pBulletMgr->fire(this->getPosX() +2, this->getPosY() - 30, PI / 2, PI, IMAGEMANAGER->findImage("circleSmallBullet"), 5.1f, 12, 12, 1, true, C_BULLET::E_BULLETTYPE::E_SPELL);

		if (_nBulletFrameCount == 0)
		{
			for (int i = 0; i < _nPower / 10 + 1; i++)
			{
				_pBulletMgr->fire(this->getPosX() +_arPowerNPosX[i], this->getPosY() - 30, PI / 2, 0, IMAGEMANAGER->findImage("redbullet"), 5.1f, 12, 12, 1, true, C_BULLET::E_BULLETTYPE::E_STRIGHT);
				_pBulletMgr->setDamage(10);
			}

			if (_nPower >= 25)
			{
				_pBulletMgr->fire(this->getPosX() + _arPowerNPosX[0]-10, this->getPosY() - 30, PI / 2, 0, IMAGEMANAGER->findImage("bullet360"), 7.1f, 20, 20, 36, true, C_BULLET::E_BULLETTYPE::E_HOMING);
				_pBulletMgr->setDamage(2);
				_pBulletMgr->fire(this->getPosX() + _arPowerNPosX[2]+10, this->getPosY() - 30, PI / 2, 0, IMAGEMANAGER->findImage("bullet360"), 7.1f, 20, 20, 36, true, C_BULLET::E_BULLETTYPE::E_HOMING);
				_pBulletMgr->setDamage(2);

			}
			//유도미사일

			_nBulletFrameCount = 10;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		useSpell();
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		powerUp();
	}
	


	if (_nBulletFrameCount != 0)
	{
		_nBulletFrameCount--;
	}


	_nFrameCount++;

	if (_nFrameCount % 5 == 0)
	{
		playAnimation();

		_nFrameCount = 0;
	}



	onCollision();

	updateSpell();
}

void C_PLAYER::render()
{
	_pImg->frameRender(getMemDC(), static_cast<int>(_fPosX) - _nWidth / 2,  static_cast<int>(_fPosY) - _nHeight / 2, _nFrameX, static_cast<int>(_ePlayerState));

	HBRUSH hBrush = CreateSolidBrush(RGB(_Color[0], _Color[1], _Color[2]));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
	EllipseMakeCenter(getMemDC(), static_cast<int>(_fPosX) , static_cast<int>(_fPosY), _nCollisionRadius * 2, _nCollisionRadius * 2);
	DeleteObject(hBrush);

	if (_bIsSpell )
	{
		pImage->alphaRender(getMemDC(), 102);
	}
}

void C_PLAYER::playAnimation()
{

	if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_IDLE)
	{
		if (_nFrameX >= 3)
		{
			_nFrameX = 0;
		}
		_nFrameX++;

	}
	else if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_LEFTMOVE)
	{
		if (_nFrameX >= 6)
		{
			_nFrameX = 4;
		}
		_nFrameX++;

	}
	else if (_ePlayerState == C_PLAYER::E_PLAYERSTATE::E_RIGHTMOVE)
	{
		if (_nFrameX < 1)
		{
			_nFrameX = 1;
		}

		_nFrameX--;

	}
	for (int i = 0; i < 3; i++)
	{
		if (_Color[i] > 5)
		{
			_Color[i]-= 10;
		}
	}

}

void C_PLAYER::powerUp()
{

	
	if (_nPower == 10)
	{
		_arPowerNPosX[0] = -10;
		_arPowerNPosX[1] = 10;
	}
	else if (_nPower == 20)
	{
		_arPowerNPosX[0] = -20;
		_arPowerNPosX[1] = 0;
		_arPowerNPosX[2] = 20;
	}


}

void C_PLAYER::setBulletMgr(C_BULLETMGR * pBulletMgr)
{
	_pBulletMgr = pBulletMgr;
}

vector<int> C_PLAYER::getScores()
{
	int	nScore = _nScore;
	_vScore.clear();
	while (nScore != 0)
	{
		_vScore.push_back(nScore % 10);
		nScore /= 10;
	}

	return _vScore;
}

void C_PLAYER::addPower(int nPoint)
{
	 if (_nPower < 40)
	 {
		 _nPower += nPoint;
	 }
	 powerUp();
}

void C_PLAYER::onCollision()
{
	if (_pBulletMgr->onPlayerCollsion(_fPosX, _fPosY, _nCollisionRadius)) {
		_Color[0] = 0xff;
		_Color[1] = 0xff;
		_Color[2] = 0xff;
	}
}

void C_PLAYER::useSpell()
{
	if (_nSpellCount > 0)
	{
		_pBulletMgr->clearBullet();
		_bIsSpell = true;
		_nSpellCount--;
	}
}

void C_PLAYER::updateSpell()
{
	if (_bIsSpell)
	{
		nRadius = pImage->alphaRound(_fPosX, _fPosY, nRadius);
		nRadius += 5;

		if (nRadius > 800)
		{
			pImage->init("image/spellBack.bmp", 600, 800, true, RGB(255, 0, 255), true);
			_bIsSpell = false;
			nRadius = 50;
		}
	}

}

void C_PLAYER::initSpell()
{
	nRadius = 1;
	pImage = new image;
	pImage->init("image/spellBack.bmp", 600, 800, true, RGB(255, 0, 255), true);
	_bIsSpell = false;
}