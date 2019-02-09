#include "stdafx.h"
#include "lastBoss.h"

C_LASTBOSS::C_LASTBOSS()
{
}

C_LASTBOSS::~C_LASTBOSS()
{
}

void C_LASTBOSS::create(float fPosX, float fPosY, float fAngle, float fSpeed)
{
	_fPosX = fPosX;				
	_fPosY = fPosY;				
	_fAngle = PI/2.0f;			
	_pImg = IMAGEMANAGER->findImage("lastBoss");
	_nWidth = _pImg->getFrameWidth();			
	_nHeight = _pImg->getFrameHeight();			
	_fSpeed = 100.0f;			
			
	_nCurrentFrameX = 0;	
	_nCurrentFrameY = 0;	
	_nAniMationFrame = 0;	
	_bIsRemove = false;			
	_nBulletReload = 0;		
	_bIsFire = false;			

	_fHurricaneAngle = 0.0f;
	_nMovingFrameCount = 0;
	_nAnimaitionFrameCount = 0;
	_eFireType = C_LASTBOSS::E_FIRETYPE::E_NONE;
	_eMoveStatus = C_LASTBOSS::E_MOVING::E_APPEAR;


	_nLife = 1;
	_nItem = 5;
	_nHp = 3000;

	_fMoveCircleCenterX = WINSIZEX/2;
	_fMoveCircleCenterY = 200;
	_fMoveTurn = 1.0f;

	_pImgEffect = IMAGEMANAGER->findImage("lbEffect");
	_nFireCount = 0;

	_bIsStartFlowor = false;

}

void C_LASTBOSS::update()
{
	if (_eMoveStatus == C_LASTBOSS::E_MOVING::E_APPEAR)
	{
		_fPosY += Mins::presentPowerY(PI + PI / 2.0f, 5.0f);

		if (_fPosY > 100)
		{
			_fPosY = 100;
			_eMoveStatus = C_LASTBOSS::E_MOVING::E_STAY;
			_eFireType = C_LASTBOSS::E_FIRETYPE::E_HERRICANE;
			_bIsFire = true;
		}
	}
	else if (_eMoveStatus == C_LASTBOSS::E_MOVING::E_STAY)
	{
		_nMovingFrameCount++;

	}
	else if (_eMoveStatus == C_LASTBOSS::E_MOVING::E_MOVE)
	{
		_eMoveStatus = C_LASTBOSS::E_MOVING::E_STAY;

		_fPosX = _fMoveCircleCenterX + Mins::presentPowerX(_fAngle, _fSpeed);
		_fPosY = _fMoveCircleCenterY + Mins::presentPowerY(_fAngle, _fSpeed);

		_fSpeed += _fMoveTurn * 1.0f;
		_fAngle += _fMoveTurn * PI / 180.0f;

		if (_fSpeed >= (float)E_HORIZENTAL || _fSpeed <= (float)E_VERTICAL)
		{
			_fMoveTurn *= -1.0f;
		}

		_nMovingFrameCount++;
	}

	if (_nMovingFrameCount % 720 == 0)
	{
		//if (_eMoveStatus == C_LASTBOSS::E_MOVING::E_STAY) {
		//	_eMoveStatus = C_LASTBOSS::E_MOVING::E_MOVE;
		//}
		//else 
		if (_eMoveStatus == C_LASTBOSS::E_MOVING::E_MOVE) {
			_eMoveStatus = C_LASTBOSS::E_MOVING::E_STAY;
		}
		_nMovingFrameCount = 0;
	}

	_nAnimaitionFrameCount++;

	if (_nAnimaitionFrameCount % 5 == 0)
	{
		_nCurrentFrameX++;
		if (_nCurrentFrameX >= _pImg->getMaxFrameX())
		{
			_nCurrentFrameX = 0;
		}
		_nAnimaitionFrameCount = 0;
	}

	if (_nLife > 4)
	{
		_bIsRemove = true;
	}


	_nBulletReload++;
	_nSmallFrameCount = 0;
	_bIsBulletClear = false;
}

void C_LASTBOSS::release()
{
	_pImg = nullptr;
	_pImgEffect = nullptr;
}

void C_LASTBOSS::render(HDC hDc)
{
	_pImgEffect->renderCenter(hDc, _fPosX, _fPosY);

	_pImg->frameRenderCenter(hDc, _fPosX, _fPosY, _nCurrentFrameX, _nCurrentFrameY);


}

void C_LASTBOSS::fire(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer)
{
	//허리케인 샷
	if (C_LASTBOSS::E_FIRETYPE::E_HERRICANE == static_cast<C_LASTBOSS::E_FIRETYPE>(_nLife))
	{
		//10도 사격
		//11도 사격
		//리로드는 10프레임
		//1번

		if (_nBulletReload % 10 == 0)
		{
			fireHurricane(pBulletMgr, pPlayer, _fHurricaneAngle);

			_fHurricaneAngle += PI/7.0f;

			_nBulletReload = 0;
		}
	}
	else if (C_LASTBOSS::E_FIRETYPE::E_TWOFLOWER == static_cast<C_LASTBOSS::E_FIRETYPE>(_nLife))
	{
		if (!_bIsStartFlowor)
		{
			initSprialPos();
			_bIsStartFlowor = true;
		}

		if (_nBulletReload % 10 == 0)
		{
			fireTwoFlower(pBulletMgr, pPlayer, _fHurricaneAngle);

			_fHurricaneAngle += PI / 7.0f;

			_nBulletReload = 0;
		}
	}
	else if (C_LASTBOSS::E_FIRETYPE::E_LEAFSTORM == static_cast<C_LASTBOSS::E_FIRETYPE>(_nLife))
	{
		if (_nBulletReload % 10 == 0)
		{
			fireLeafStorm(pBulletMgr, pPlayer);
			_nBulletReload = 0;
		}
	}
	else if (C_LASTBOSS::E_FIRETYPE::E_ARC == static_cast<C_LASTBOSS::E_FIRETYPE>(_nLife))
	{
		if (_nBulletReload % 10 == 0)
		{
			fireArc(pBulletMgr, pPlayer,_fPosX, _fPosY);
			fireArc(pBulletMgr, pPlayer, _fPosX + 170, _fPosY +  170);
			fireArc(pBulletMgr, pPlayer, _fPosX - 170, _fPosY +  170);
		}

		if (_nBulletReload % 60 == 0)
		{
			fireCircle(pBulletMgr, pPlayer, _fPosX, _fPosY);
			fireCircle(pBulletMgr, pPlayer, _fPosX + 170, _fPosY + 170);
			fireCircle(pBulletMgr, pPlayer, _fPosX - 170, _fPosY + 170);
		}

		if (_nBulletReload >= 250)
		{
			fireVine(pBulletMgr, pPlayer, _fPosX, _fPosY);
			fireVine(pBulletMgr, pPlayer, _fPosX + 170, _fPosY + 170);
			fireVine(pBulletMgr, pPlayer, _fPosX - 170, _fPosY + 170);
		}
	}

	
	if (_nFireCount > 200 * _nLife)
	{
		pBulletMgr->goHurricane();
		_nFireCount = 0;
		_nBulletReload = 0;
	}
}

bool C_LASTBOSS::checkRemove()
{
	return _bIsRemove;
}

bool C_LASTBOSS::checkFireOk()
{
	return _bIsFire;
}

float C_LASTBOSS::getPosX()
{
	return _fPosX;
}

float C_LASTBOSS::getPosY()
{
	return _fPosY;
}

int C_LASTBOSS::getRadius()
{
	return _nWidth - 10;
}

void C_LASTBOSS::damage(int nDamage)
{
	_nHp -= nDamage;

	if (_nHp <= 0)
	{
		_nLife++;
		_nHp = 3000;
		_nFireCount = 0;
		_nBulletReload = 0;
		_bIsBulletClear = true;
	}
}

int C_LASTBOSS::getHp()
{
	return _nHp;
}

int C_LASTBOSS::getItem()
{
	return 0;
}

bool C_LASTBOSS::bulletClear()
{
	return _bIsBulletClear;
}

void C_LASTBOSS::fireHurricane(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer,float foffSetAngle)
{

	float fAngle = foffSetAngle;
	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(_fPosX, _fPosY, fAngle, 0.1f, IMAGEMANAGER->findImage("colorBullet"), 0.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_HERICAIN);
		fAngle += PI2/6.0f;
		pBulletMgr->setFrameY(2);
	}
	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(_fPosX, _fPosY, foffSetAngle, -0.1f, IMAGEMANAGER->findImage("colorBullet"), 0.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_HERICAIN);
		foffSetAngle -= PI2 / 6.0f;
		pBulletMgr->setFrameY(2);
	}

	_nFireCount += 12;
}

void C_LASTBOSS::fireTwoFlower(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer, float foffSetAngle)
{

	float fAngle = foffSetAngle;
	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(WINSIZEX/2, WINSIZEY/2, fAngle, 0.1f, IMAGEMANAGER->findImage("colorBullet"), 10.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_SLIDER);
		fAngle += PI2 / 6.0f;
		pBulletMgr->setFrameY(3);
	}
	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(_fPosX, _fPosY, foffSetAngle, -0.1f, IMAGEMANAGER->findImage("colorBullet"), 3.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_SLIDER);
		foffSetAngle -= PI2 / 6.0f;
	}

	fAngle = 0.0f;
	updateSprialPos();
	for (int i = 0; i < 8; i++)
	{
		pBulletMgr->fire(_arFosSpiralPosX[i], _arFosSpiralPosY[i], _arFosAngle[i], 0.0f, IMAGEMANAGER->findImage("colorBullet"), 25.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHTSLOW);
		pBulletMgr->setBottomRadius(2.5f);
		pBulletMgr->setFrameY(1);
		fAngle += PI2 / 8.0f;
	}


	_nFireCount += 12;
}

void C_LASTBOSS::fireLeafStorm(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer)
{
	float fAngle = 0.0f;
	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(WINSIZEX / 2, WINSIZEY / 2, fAngle, 0.0f, IMAGEMANAGER->findImage("colorBullet"), 10.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_LEAFSTORM);
		fAngle += PI2 / 6.0f;
		pBulletMgr->setFrameY(1);
		pBulletMgr->setBottomRadius(5.0f);
		pBulletMgr->setLimitedRadius(15.0f);
	}
	fAngle = 0.0;
	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(_fPosX, _fPosY,fAngle, 0, IMAGEMANAGER->findImage("colorBullet"), 3.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_LEAFSTORM);
		fAngle -= PI2 / 6.0f;
		pBulletMgr->setFrameY(3);
		pBulletMgr->setBottomRadius(1.0f);
		pBulletMgr->setLimitedRadius(9.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(WINSIZEX / 2, _fPosY+ 100, fAngle, 0, IMAGEMANAGER->findImage("colorBullet"), 6.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_LEAFSTORM);
		fAngle -= PI2 / 6.0f;
		pBulletMgr->setFrameY(0);
		pBulletMgr->setBottomRadius(1.0f);
		pBulletMgr->setLimitedRadius(10.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(_fPosX - 200, _fPosY, fAngle, 0, IMAGEMANAGER->findImage("colorBullet"), 5.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_LEAFSTORM);
		fAngle -= PI2 / 6.0f;
		pBulletMgr->setFrameY(2);
		pBulletMgr->setBottomRadius(4.0f);
		pBulletMgr->setLimitedRadius(7.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		pBulletMgr->fire(_fPosX + 200, _fPosY, fAngle, 0, IMAGEMANAGER->findImage("colorBullet"), 5.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_LEAFSTORM);
		fAngle -= PI2 / 6.0f;
		pBulletMgr->setFrameY(2);
		pBulletMgr->setBottomRadius(4.0f);
		pBulletMgr->setLimitedRadius(7.0f);
	}

	_nFireCount += 30;
}

void C_LASTBOSS::fireArc(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer, float fCirclePosX, float fCirclePosY)
{
	float fAngle = PI + PI/3.0f;

	
	pBulletMgr->fire(fCirclePosX, fCirclePosY - 100.0f, fAngle, 0.0f, IMAGEMANAGER->findImage("circleBullet"), 2.1f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_TRUETRI);
	pBulletMgr->serFrameX(1);
	pBulletMgr->setLimitedRadius(100.0f);
	pBulletMgr->setCircleX(fCirclePosX);
	pBulletMgr->setCircleY(fCirclePosY);
	fAngle = PI/3.0f * 2.0f;
	pBulletMgr->fire(fCirclePosX, fCirclePosY + 100.0f, fAngle, 0.0f, IMAGEMANAGER->findImage("circleBullet"), 2.1f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_INVERSETRI);
	pBulletMgr->serFrameX(1);
	pBulletMgr->setLimitedRadius(100.0f);
	pBulletMgr->setCircleX(fCirclePosX);
	pBulletMgr->setCircleY(fCirclePosY);
	fAngle = 0.0f;
	pBulletMgr->fire(fCirclePosX + Mins::presentPowerX(0.0f,100.0f), fCirclePosY + Mins::presentPowerY(0.0f, 100.0f), fAngle, 0.0f, IMAGEMANAGER->findImage("circleBullet"),100.0f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_CIRCLE);
	pBulletMgr->serFrameX(1);
	pBulletMgr->setLimitedRadius(100.0f);
	pBulletMgr->setCircleX(fCirclePosX);
	pBulletMgr->setCircleY(fCirclePosY);

	_nFireCount += 3;
}

void C_LASTBOSS::fireCircle(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer, float fCirclePosX, float fCirclePosY)
{
	float fAngle = 0.0f;

	for (int i = 0; i < 10; i++)
	{
		pBulletMgr->fire(fCirclePosX, fCirclePosY, fAngle, RND->getFromFloatTo(0.0f,PI2), IMAGEMANAGER->findImage("colorBullet"), 3.1f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
		fAngle += PI2 / 10.0f;
		pBulletMgr->setFrameY(2);
		pBulletMgr->setBottomRadius(4.0f);
		pBulletMgr->setLimitedRadius(7.0f);
	}

	_nFireCount += 10;
}

void C_LASTBOSS::fireVine(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer, float fCirclePosX, float fCirclePosY)
{
	pBulletMgr->fire(fCirclePosX - 2, fCirclePosY, PI+PI/2.0f, 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 3.1f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_SPELL);
	pBulletMgr->serFrameX(_nSmallFrameCount);
	_nSmallFrameCount++;

	pBulletMgr->fire(fCirclePosX + 2, fCirclePosY, PI + PI / 2.0f, PI, IMAGEMANAGER->findImage("circleSmallBullet"), 3.1f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_SPELL);
	pBulletMgr->serFrameX(_nSmallFrameCount);
	_nSmallFrameCount++;

	int nMax = IMAGEMANAGER->findImage("circleSmallBullet")->getMaxFrameX();
	if (_nSmallFrameCount >= 7)
	{
		_nSmallFrameCount = 0;
	}
	_nFireCount += 2;
}

void C_LASTBOSS::initSprialPos()
{
	float	fAngle = 0.0f;
	for (int i = 0; i < 8; i++)
	{
		_arFosAngle[i] = fAngle;
		_arFosSpiralPosX[i] = WINSIZEX/2.0f + Mins::presentPowerX(_arFosAngle[i], 5.0f);
		_arFosSpiralPosY[i] = WINSIZEY/2.0f + Mins::presentPowerY(_arFosAngle[i], 5.0f);
		fAngle += PI2 / 8.0f;
	}

}

void C_LASTBOSS::updateSprialPos()
{
	for (int i = 0; i < 8; i++)
	{
		_arFosAngle[i] += PI2/36.0f;
		_arFosSpiralPosX[i] = WINSIZEX / 2.0f + Mins::presentPowerX(_arFosAngle[i], 5.0f);
		_arFosSpiralPosY[i] = WINSIZEY / 2.0f + Mins::presentPowerY(_arFosAngle[i], 5.0f);
	}
}


