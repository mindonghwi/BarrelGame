#include "stdafx.h"
#include "boss.h"

C_BOSS::C_BOSS()
{
}

C_BOSS::~C_BOSS()
{
}

void C_BOSS::create(float fPosX, float fPosY, float fAngle, float fSpeed)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_fAngle = fAngle;
	_pImg = IMAGEMANAGER->findImage("boss");
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();
	_fSpeed = fSpeed;
	_nCurrentFrameX = 0;
	_nCurrentFrameY = 0;
	_nAniMationFrame = 0;
	_bIsRemove = false;
	_nBulletReload = 0;
	_bIsFire = false;
	//_bIsStartVertex = false;
	//_bIsStartStarOfDavid = false;
	//_bIsStartUnlimited = false;
	_fChangePlusMinus = 1.0f;
	_eMoveStatus = C_BOSS::E_MOVING::E_APPEAR;
	_fChargingRotate = 0;
	//_bIsStartCharging = false;
	_eFireType = C_BOSS::E_FIRETYPE::E_NONE;
	_nTurn = 1;

	for (int i = 0; i < static_cast<int>(C_BOSS::E_MOVING::E_MAX); i++)
	{
		_arStartMoving[i] = false;
	}
	for (int i = 0; i < static_cast<int>(C_BOSS::E_FIRETYPE::E_MAX); i++)
	{
		_arStartFire[i] = false;
	}
	_pImgEffect = IMAGEMANAGER->findImage("effect");

	initCremora();

	for (int i = 0; i < 19; i++)
	{
		_arEffectPosX[i] = -2000;
		_arEffectPosY[i] = -2000;
		_arEFCurrentX[i] = -1;
	}
	_nEffectIndex = 0;
	_fBangAngle = 0.0f;
	_fBangRadius = 100.0f;
	_nHp = 10000;

}

void C_BOSS::update()
{
	//이동
	if (_eMoveStatus == C_BOSS::E_MOVING::E_NONE)
	{

	}
	else if (_eMoveStatus == C_BOSS::E_MOVING::E_APPEAR)
	{
		appear();
	}
	else if (_eMoveStatus == C_BOSS::E_MOVING::E_STAROFDAVID)
	{
		moveStarOfDavid();
	}
	else if (_eMoveStatus == C_BOSS::E_MOVING::E_UNLIMITED)
	{
		moveUnlimited();
	}
	else if (_eMoveStatus == C_BOSS::E_MOVING::E_VERTEX)
	{
		moveVertex();
	}
	else if (_eMoveStatus == C_BOSS::E_MOVING::E_STAND)
	{
		updateEffect();
	}
	if (_fAngle >= PI2)
	{
		_fAngle = _fAngle - PI2;
	}
	if (_fAngle <= 0.0f)
	{
		_fAngle = PI2 + _fAngle;
	}

	//사격

	//죽음체크

	//애니메이션 상태체크
	_nAniMationFrame++;

	if (_nAniMationFrame % 5 == 0)
	{
		_nAniMationFrame = 0;
		_nCurrentFrameX++;

		if (_nCurrentFrameX >= 4)
		{
			_nCurrentFrameX = 0;
		}
		else if (_nCurrentFrameX >= 4 && _eMoveStatus == C_BOSS::E_MOVING::E_VERTEX && _eMoveStatus == C_BOSS::E_MOVING::E_UNLIMITED)
		{
			_nCurrentFrameX = 3;
		}
	}

	if (_fAngle > PI/2.0f && _fAngle < PI+PI/2.0f)
	{
		if (_eMoveStatus == C_BOSS::E_MOVING::E_VERTEX && _eMoveStatus == C_BOSS::E_MOVING::E_UNLIMITED)
		{
			_nCurrentFrameY = 1;
		}
	}
	else if (_fAngle < PI / 2.0f || _fAngle > PI + PI / 2.0f)
	{
		if (_eMoveStatus == C_BOSS::E_MOVING::E_VERTEX && _eMoveStatus == C_BOSS::E_MOVING::E_UNLIMITED)
		{
			_nCurrentFrameY = 2;
		}
	}
	else if (fabsf(_fAngle - PI/2.0f)<= FLT_EPSILON || fabsf(_fAngle - (PI + PI / 2.0f)) <= FLT_EPSILON)
	{
		_nCurrentFrameY = 0;
	}
	if (_eFireType != C_BOSS::E_FIRETYPE::E_NONE)
	{
		_nCurrentFrameY = 3;
	}
	
	for (int i = 0; i < 6; i++)
	{
		_arCremoraFrameX[i]++;
		if (_arCremoraFrameX[i] >= 7)
		{
			_arCremoraFrameX[i] = 0;
		}
	}

}

void C_BOSS::release()
{
	_pImg = nullptr;
}

void C_BOSS::render(HDC hDc)
{
	_pImg->frameRenderCenter(hDc, static_cast<int>(_fPosX), static_cast<int>(_fPosY), _nCurrentFrameX, _nCurrentFrameY);

	//for (int i = 0; i < 12; i++)
	//{
	//	_pImgCremora->frameRenderCenter(hDc, static_cast<int>(_arCircleOfPosX[i]), static_cast<int>(_arCircleOfPosY[i]), 0, 0);
	//}
	renderEffect(hDc);
	renderCremora(hDc);


	//char str[64];
	//sprintf_s(str, "%d", getHp());
	//TextOut(hDc, 20, 40, str, strlen(str));
}

void C_BOSS::fire(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer)
{
	if (_eFireType == C_BOSS::E_FIRETYPE::E_NONE && _eMoveStatus == C_BOSS::E_MOVING::E_NONE)
	{
		if (pBulletMgr->getNotEnemyBullet())
		{
			//한턴씩 나오게 한다
			_nTurn++; //= RND->getFromIntTo(static_cast<int>(C_BOSS::E_FIRETYPE::E_CHARGING), static_cast<int>(C_BOSS::E_FIRETYPE::E_MAX));
			if (_nTurn >= static_cast<int>(C_BOSS::E_FIRETYPE::E_MAX))
			{
				_nTurn = 1;
			}
			_eMoveStatus = static_cast<C_BOSS::E_MOVING>(_nTurn);
			_eFireType = static_cast<C_BOSS::E_FIRETYPE>(_nTurn);
			_arStartFire[static_cast<const int>(_nTurn)] = true;
			_arStartMoving[static_cast<const int>(_nTurn)] = true;

			//임시
			_bIsShotFlower = true;
			clearEffect();
			_nBulletReload = 0;
		}
	}
	else if (_eFireType == C_BOSS::E_FIRETYPE::E_CHARGING)
	{
		charzingShot(pBulletMgr, pPlayer);
	}
	else if (_eFireType == C_BOSS::E_FIRETYPE::E_SHAKESHOT)
	{
		shakeShot(pBulletMgr, pPlayer);
		initFlowerPos();

		flowerShot(pBulletMgr, pPlayer);
	}
	else if (_eFireType == C_BOSS::E_FIRETYPE::E_CREMORA)
	{
		cramoreShot(pBulletMgr, pPlayer);
	}
	else if (_eFireType == C_BOSS::E_FIRETYPE::E_CIRCLE)
	{
		circleDoubleShot(pBulletMgr, pPlayer);
	}
	else if (_eFireType == C_BOSS::E_FIRETYPE::E_BAMGBAMG)
	{
		bangbangShot(pBulletMgr, pPlayer);
	}
}

bool C_BOSS::checkRemove()
{
	return _bIsRemove;
}

bool C_BOSS::checkFireOk()
{
	return _bIsFire;
}

float C_BOSS::getPosX()
{
	return _fPosX;
}

float C_BOSS::getPosY()
{
	return _fPosY;
}

int C_BOSS::getRadius()
{
	return _nWidth;
}

void C_BOSS::damage(int nDamage)
{
	_nHp -= nDamage;
	if (_nHp <= 0)
	{
		_bIsRemove = true;
	}
}

int C_BOSS::getHp()
{
	return _nHp;
}

int C_BOSS::getItem()
{
	return 0;
}

bool C_BOSS::bulletClear()
{
	return false;
}

void C_BOSS::charzingShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{

	if (_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CHARGING)])
	{
		_nChargingCycle = WINSIZEY;
		_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CHARGING)] = false;
	}

	for (int i = 0; i < 10; i++)
	{
		pBulletMgr->fire(_fPosX + Mins::presentPowerX(_fChargingRotate, static_cast<float>(_nChargingCycle)), _fPosY + Mins::presentPowerY(_fChargingRotate, static_cast<float>(_nChargingCycle)), _fChargingRotate, 0.0f,
			IMAGEMANAGER->findImage("circleBullet"), 0.0f, 28, 28, 1, false, C_BULLET::E_BULLETTYPE::E_CHASINGSHOT, _nChargingCycle);

		_fChargingRotate -= PI / 18.0f;
	}

	_nChargingCycle -= 20;

	if (_nChargingCycle == 0)
	{
		_eFireType = C_BOSS::E_FIRETYPE::E_NONE;
		//_bIsFire = false;
	}

	//서있는 상태에서 사용
}


void C_BOSS::cramoreShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{
	//육망성이랑 연계하자
	if (_nCremoraIndex >= 6 && _nBulletReload % 5 == 0)
	{
		if (_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CREMORA)])
		{
			_nBulletReload = 0;
			_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CREMORA)] = false;
		}
		for (int i = 0; i < 6; i++)
		{
			//for (int j = 0; j < 4; j++)
			{
				pBulletMgr->fire(_arCremoraPosX[i], _arCremoraPosY[i], _arSpiralAngle[0], 0.0f, IMAGEMANAGER->findImage("colorBullet"), 1.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
				pBulletMgr->setFrameY(RND->getInt(4));
			}
		}

		for (int j = 0; j < 4; j++)
		{
			_arSpiralAngle[j] += PI / 36.0f;

			if (fabsf(_arSpiralAngle[j] - PI2) <= FLT_EPSILON)
			{
				_arSpiralAngle[j] = 0;
			}
		}

	}
	_nBulletReload++;

	if (_nBulletReload > 500)
	{
		_eFireType = C_BOSS::E_FIRETYPE::E_NONE;
		releaseCremora();
	}
}

void C_BOSS::speedShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{

}

void C_BOSS::shakeShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{
	//가로이동과 연계
	//음 플레이어 위치보고 

	if (_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_SHAKESHOT)])
	{
		_nBulletReload = 0;
		_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_SHAKESHOT)] = false;
		_fWaveAngle = PI;
		_fTurnAngle = 1.0f;
	}

	_nBulletReload++;

	if (_nBulletReload % 5 == 0)
	{
		float fAngle = getAngle(WINSIZEX / 2.0f, 200.0f, pPlayer->getPosX(), pPlayer->getPosY());
		float fSixtyOffSet = PI / 3.0f;

		//pBulletMgr->fire(_fPosX, _fPosY, fAngle - fSixtyOffSet, PI,
		//	IMAGEMANAGER->findImage("circleBullet"), 5.0f, 20, 20, 1, false, C_BULLET::E_BULLETTYPE::E_WAVE);
		//pBulletMgr->fire(_fPosX, _fPosY, fAngle, 0.0f,
		//	IMAGEMANAGER->findImage("circleBullet"), 5.0f, 20, 20, 1, false, C_BULLET::E_BULLETTYPE::E_WAVE);
		//pBulletMgr->fire(_fPosX, _fPosY, fAngle + fSixtyOffSet, PI,
		//	IMAGEMANAGER->findImage("circleBullet"), 5.0f, 20, 20, 1, false, C_BULLET::E_BULLETTYPE::E_WAVE);

		pBulletMgr->fire(_fPosX + Mins::presentPowerX(_fWaveAngle, 50.0f), _fPosY + Mins::presentPowerY(_fWaveAngle, 50.0f), _fWaveAngle, 0.0f,
			IMAGEMANAGER->findImage("circleBullet"), 5.0f, 20, 20, 1, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
		_fWaveAngle += _fTurnAngle * PI / 6.0f;
		if (_fWaveAngle > PI2 || _fWaveAngle < PI)
		{
			_fTurnAngle *= -1.0f;
		}

	}



	if (_nBulletReload > 500)
	{
		_eFireType = C_BOSS::E_FIRETYPE::E_NONE;
	}
}

void C_BOSS::circleDoubleShot(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer)
{
	//육망성이랑 연계하자

	if (_nBulletReload % 6 == 0)
	{
		if (_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CIRCLE)])
		{
			_nBulletReload = 0;
			_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CIRCLE)] = false;
			initCircle();
		}

		for (int i = 0; i < 12; i++)
		{
			pBulletMgr->fire(_arCircleOfPosX[i], _arCircleOfPosY[i], PI2 / 12.0f * static_cast<float>(i), PI / 3.0f, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);

			pBulletMgr->fire(_arCircleOfPosX[i], _arCircleOfPosY[i], PI2 / 12.0f * static_cast<float>(i), -1.0f * PI / 3.0f, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
		}
		//initCircle();

	}

	if (_nBulletReload % 20 == 0)
	{
		for (int i = 0; i < 36; i++)
		{
			pBulletMgr->fire(_fPosX, _fPosY, PI2 / 36.0f * static_cast<float>(i), 0.0f, IMAGEMANAGER->findImage("circleBullet"), 6.0f, 20, 20, 1, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
			pBulletMgr->serFrameX(2);
		}
	}

	_nBulletReload++;

	if (_nBulletReload > 500)
	{
		_eFireType = C_BOSS::E_FIRETYPE::E_NONE;
	}

}

void C_BOSS::flowerShot(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer)
{
	if (_bIsShotFlower)
	{
		if (_nBulletReload % 120 == 0)
		{
			//9개의 꽃
			for (int i = 0; i < 9; i++)
			{
				//7장
				for (int j = 0; j < 7; j++)
				{
					//1장에 18개
					for (int k = 0; k < 18; k++)
					{
						float fX = _arFlowerPosX[i] + Mins::presentPowerX(PI2 / 7.0f*static_cast<float>(j), 60.0f) + Mins::presentPowerX(PI2 / 18.0f * static_cast<float>(k), 30.0f);
						float fY = _arFlowerPosY[i] + Mins::presentPowerY(PI2 / 7.0f*static_cast<float>(j), 60.0f) + Mins::presentPowerY(PI2 / 18.0f * static_cast<float>(k), 30.0f);


						pBulletMgr->fire(fX, fY, PI2 / 7.0f*static_cast<float>(j), 0.0f, IMAGEMANAGER->findImage("flowerBullet"), 3.0f, 20, 20, 1, false, C_BULLET::E_BULLETTYPE::E_MOVEDELEYRANDOM, 60);
						pBulletMgr->serFrameX(7);
					}
				}
			}
		}
	}

}

void C_BOSS::bangbangShot(C_BULLETMGR * pBulletMgr, C_PLAYER * pPlayer)
{
	float fPlayerX = pPlayer->getPosX();
	float fPlayerY = pPlayer->getPosY();

	_fBangPosX = fPlayerX + Mins::presentPowerX(_fBangAngle, _fBangRadius);
	_fBangPosY = fPlayerY + Mins::presentPowerY(_fBangAngle, _fBangRadius);

	createEffect();


	_fBangAngle += 0.2f;

	if (_fBangRadius < 200.0f)
	{
		_fBangRadius += 1.0f;

	}




	if (_fBangPosX > pPlayer->getPosX())
	{
		pBulletMgr->fire(_fBangPosX, _fBangPosY, PI / 4.0f, 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 0.06f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_DELEYTURN, 700.0f);
	}
	else
	{
		pBulletMgr->fire(_fBangPosX, _fBangPosY, PI + PI / 4.0f, 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 0.06f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_DELEYTURN, 700.0f);
	}
	pBulletMgr->serFrameX(2);


	if (_fBangPosY > pPlayer->getPosY())
	{
		pBulletMgr->fire(_fBangPosX, _fBangPosY, PI2 - PI / 4.0f, 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 0.06f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_DELEYTURN, 700.0f);
	}
	else
	{
		pBulletMgr->fire(_fBangPosX, _fBangPosY, PI - PI / 4.0f, 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 0.06f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_DELEYTURN, 700.0f);
	}
	pBulletMgr->serFrameX(2);


	if (_nBulletReload % 50 == 0)
	{
		pBulletMgr->fire(_fBangPosX, _fBangPosY, getAngle(_fBangPosX, _fBangPosY, fPlayerX, fPlayerY), 0.0f, IMAGEMANAGER->findImage("circleSmallBullet"), 5.6f, 10, 10, 1, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
		pBulletMgr->serFrameX(4);
	}



	pBulletMgr->serFrameX(2);

	float fAngle = PI - PI2 / 18.0f;

	for (int i = 0; i < 18; i++)
	{
		pBulletMgr->fire(fPlayerX +Mins::presentPowerX( PI2/ 18.0f *static_cast<float>(i),200.0f),
			fPlayerY + Mins::presentPowerY(PI2 / 18.0f * static_cast<float>(i ), 200.0f),
			fAngle, 0.0f, IMAGEMANAGER->findImage("colorBullet"), 2.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_LAZER, 90000.0f);
		fAngle += PI2 / 18.0f;
	}

	_nBulletReload++;
	if (_nBulletReload > 2000)
	{
		_eFireType = C_BOSS::E_FIRETYPE::E_NONE;
		_eMoveStatus = C_BOSS::E_MOVING::E_NONE;
		clearEffect();
	}
}




void C_BOSS::appear()
{
	if (_fPosY > WINSIZEY / 4.0f)
	{
		//_bIsStartVertex = true;
		//_eMoveStatus = C_BOSS::E_MOVING::E_VERTEX;
		if (!_bIsFire)
		{
			_eFireType = C_BOSS::E_FIRETYPE::E_CHARGING;
			_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_CHARGING)] = true;
		}
		_bIsFire = true;
		_eMoveStatus = C_BOSS::E_MOVING::E_NONE;

		_nCountVertex = 0;
		return;
	}

	_fAngle = PI + PI / 2.0f;
	_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);
}

void C_BOSS::moveVertex()
{
	//탈출조건 만들기
	if (_nCountVertex > 3)
	{
		//_eMoveStatus = C_BOSS::E_MOVING::E_STAROFDAVID;
		//_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_STAROFDAVID)] = true;
		_eMoveStatus = C_BOSS::E_MOVING::E_NONE;
	}

	//위치는 다시 원 중앙쪽 위치로 이동 되어야한다 끝날때
	if (_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_VERTEX)])
	{
		_fAngle = 0;
		_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_VERTEX)] = false;
	}

	if (_fPosX > WINSIZEX - 100 || _fPosX < 100)
	{
		_fAngle += PI;
		_nCountVertex++;
	}

	_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);
	_fPosX += Mins::presentPowerX(_fAngle, _fSpeed);
}

void C_BOSS::moveStarOfDavid()
{
	//PI/3.0f//60도
	// / _ \   | \ - /  |이런식으로 이동
	if (_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_STAROFDAVID)])
	{
		_fAngle = PI + (PI / 3.0f);
		_fPosX = WINSIZEX / 2.0f;
		_nMovingFrameCount = 1;
		_nCremoraIndex = 0;
		_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_STAROFDAVID)] = false;
	}

	//육망성 전환 코드 짜기
	//프레임 단위로 짜를까?
	// 정삼각형 만듬
	if (_nMovingFrameCount % E_STAROFDAVIDTURNFRAME == 0 && _nMovingFrameCount <= E_STAROFDAVIDTURNFRAME * 3)
	{
		_fAngle += 2.0f * PI / 3.0f;
		createCremora(_nCremoraIndex);
	}
	//하강운동
	else if (_nMovingFrameCount <= E_STAROFDAVIDTURNFRAME * 4 && _nMovingFrameCount > E_STAROFDAVIDTURNFRAME * 3)
	{
		_fAngle = PI + PI / 2.0f;
	}
	//역삼각형 전환
	else if (_nMovingFrameCount == E_STAROFDAVIDTURNFRAME * 4 + 1)
	{
		_fAngle = 2.0f * PI / 3.0f;
		createCremora(_nCremoraIndex);

	}
	//역삼각형 그리기
	else if (_nMovingFrameCount % E_STAROFDAVIDTURNFRAME == 0 && _nMovingFrameCount >= E_STAROFDAVIDTURNFRAME * 4 + 1)
	{
		_fAngle -= 2.0f * PI / 3.0f;
		createCremora(_nCremoraIndex);
	}
	else if (_nMovingFrameCount <= E_STAROFDAVIDTURNFRAME * 8 && _nMovingFrameCount > E_STAROFDAVIDTURNFRAME * 7)
	{
		_fAngle = PI / 2.0f;

	}
	_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);
	_fPosX += Mins::presentPowerX(_fAngle, _fSpeed);

	//모든 이동이 끝났으면 처리하는 함수
	if (_nMovingFrameCount == E_STAROFDAVIDTURNFRAME * 8)
	{
		//_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_UNLIMITED)] = true;
		//_eMoveStatus = C_BOSS::E_MOVING::E_UNLIMITED;
		_eMoveStatus = C_BOSS::E_MOVING::E_NONE;
	}

	//프레임 이동
	_nMovingFrameCount++;
}

void C_BOSS::moveUnlimited()
{
	//두 중점을 잡는다 _fPosX는 _fPosX - 100, _fPosX + 100와 _fPosY는 그대로
	if (_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_UNLIMITED)])
	{
		_arCirclePosX[0] = _fPosX - 100.0f;
		_arCirclePosX[1] = _fPosX + 100.0f;
		_fCirclePosY = _fPosY;
		_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_UNLIMITED)] = false;
		_nCircleIndex = 0;
		_fAngle = 0.0f;
		_nMovingFrameCount = 0;
	}

	//5도씩 회전
	_fAngle += PI2 / 72.0f * _fChangePlusMinus;

	_fPosY = _fCirclePosY + Mins::presentPowerY(_fAngle, 100.0f);
	_fPosX = _arCirclePosX[_nCircleIndex] + Mins::presentPowerX(_fAngle, 100.0f);

	//다른 원으로 넘어가기
	if (fabsf(PI2 - _fAngle) <= FLT_EPSILON && _nCircleIndex == 0)
	{
		_fAngle = PI;
		_nCircleIndex++;
		_fChangePlusMinus *= -1.0f;
	}
	else if (fabsf(PI - _fAngle) <= FLT_EPSILON && _nCircleIndex == 1)
	{
		//회전 종료를 하던지 다시 회전 시키든지 일단 다시 회전으로 짜둔다
		_fAngle = 0.0f;
		_nCircleIndex = 0;
		_fChangePlusMinus *= -1.0f;
	}

	if (_nMovingFrameCount == 500)
	{
		//_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_UNLIMITED)] = true;
		//_eMoveStatus = C_BOSS::E_MOVING::E_UNLIMITED;
		_eMoveStatus = C_BOSS::E_MOVING::E_NONE;
	}

	//프레임 이동
	_nMovingFrameCount++;
}

void C_BOSS::createCremora(int& nIndex)
{
	if (nIndex > 5)
	{
		return;
	}

	_arCremoraPosX[nIndex] = _fPosX;
	_arCremoraPosY[nIndex] = _fPosY;
	_arCremoraFrameX[nIndex] = 0;

	nIndex++;
}

void C_BOSS::initCremora()
{
	//크레모아 초기화
	for (int i = 0; i < 6; i++)
	{
		_arCremoraPosX[i] = -2000;
		_arCremoraPosY[i] = -2000;
		_arCremoraFrameX[i] = 0;
	}
	float fAngle = 0;
	for (int i = 0; i < 4; i++)
	{
		_arSpiralAngle[i] = fAngle;
		fAngle += PI / 2.0f;
	}

	_pImgCremora = IMAGEMANAGER->findImage("cremora");
	_nCremoraIndex = 0;
}

void C_BOSS::renderCremora(HDC hDc)
{
	for (int i = 0; i < _nCremoraIndex; i++)
	{
		_pImgCremora->frameRenderCenter(hDc, (int)_arCremoraPosX[i], (int)_arCremoraPosY[i], (int)_arCremoraFrameX[i], 0);
	}
}

void C_BOSS::releaseCremora()
{
	_nCremoraIndex = 0;
	float fAngle = 0;
	for (int i = 0; i < 4; i++)
	{
		_arSpiralAngle[i] = fAngle;
		fAngle += PI / 2.0f;
	}
}

void C_BOSS::initCircle()
{
	for (int i = 0; i < 12; i++)
	{
		_arCircleOfPosX[i] = _fPosX + Mins::presentPowerX(PI2 / 12.0f * static_cast<float>(i), 100.0f);
		_arCircleOfPosY[i] = _fPosY + Mins::presentPowerY(PI2 / 12.0f * static_cast<float>(i), 100.0f);
	}

}

void C_BOSS::initFlowerPos()
{
	for (int i = 0; i < 9; i++)
	{
		_arFlowerPosX[i] = _fPosX + Mins::presentPowerX(PI2 / 9.0f * static_cast<float>(i), 50.0f);
		_arFlowerPosY[i] = _fPosY + Mins::presentPowerY(PI2 / 9.0f * static_cast<float>(i), 50.0f);
	}

}

void C_BOSS::createEffect()
{

	_arEffectPosX[_nEffectIndex] = _fBangPosX;
	_arEffectPosY[_nEffectIndex] = _fBangPosY;
	_arEFCurrentX[_nEffectIndex] = 0;
	_nEffectIndex++;
	if (_nEffectIndex >= 19)
	{
		_nEffectIndex = 0;
	}
}

void C_BOSS::releaseEffect(int nIndex)
{
	_arEffectPosX[nIndex] = -2000;
	_arEffectPosX[nIndex] = -2000;
	_arEFCurrentX[nIndex] = -1;
}

void C_BOSS::updateEffect()
{
	for (int i = 0; i < 19; i++)
	{
		if (_arEFCurrentX[i] == -1) continue;
		_arEFCurrentX[i]++;
		if (_arEFCurrentX[i] >= 19)
		{
			releaseEffect(i);
		}
	}
}

void C_BOSS::renderEffect(HDC hdc)
{
	for (int i = 0; i < 19; i++)
	{
		if (_arEFCurrentX[i] == -1) continue;

		_pImgEffect->frameRenderCenter(hdc, (int)_arEffectPosX[i], (int)_arEffectPosY[i], (int)_arEFCurrentX[i], 0);
	}

}

void C_BOSS::clearEffect()
{
	for (int i = 0; i < 19; i++)
	{
		_arEffectPosX[i] = -2000;
		_arEffectPosX[i] = -2000;
		_arEFCurrentX[i] = -1;
	}

}
