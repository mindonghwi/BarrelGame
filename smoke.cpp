#include "stdafx.h"
#include "smoke.h"

C_SMOKE::C_SMOKE() :
	_fAngle(0.0f),
	_fPosX(0.0f),
	_fPosY(0.0f),
	_nWidth(0),
	_nHeight(0),
	_fSpeed(0),
	_pImg(nullptr),
	_nCurrentFrameX(0),
	_eMovePhase(C_SMOKE::E_MOVEPHASE::E_NONE),
	_bIsRemove(false),
	_nCircleCycleCount(0)
{
}

C_SMOKE::~C_SMOKE()
{
}

void C_SMOKE::create(float fPosX, float fPosY, float fAngle, float fSpeed)
{
	//생성할때 
	_fAngle = fAngle;
	_fPosX = fPosX;
	_fPosY = fPosY;
	_fSpeed = fSpeed;
	_pImg = IMAGEMANAGER->findImage("smoke");
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();
	_nCurrentFrameX = 0;
	_bIsRemove = false;
	_eMovePhase = C_SMOKE::E_MOVEPHASE::E_STRIGHT;
	_nAniFrameCount = 0;
	_nCircleCycleCount = 0;

	_nHp = 100;
}

void C_SMOKE::update()
{
	//가로이동
	//원운동
	// ----------
	//       /   \
	//       \   /
	//이동
	if (_eMovePhase == C_SMOKE::E_MOVEPHASE::E_STRIGHT)
	{
		_fPosX += Mins::presentPowerX(_fAngle, _fSpeed);
		_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);

		//운동 바꾸기
		if (_fPosX > WINSIZEX / 2 && _fAngle == 0)
		{
			_fCircleCenterX = WINSIZEX / 2;
			_fCircleCenterY = _fPosY + 150.0f;
			_fAngle = PI / 2;
			_fPosX = WINSIZEX / 2;
			_eMovePhase = C_SMOKE::E_MOVEPHASE::E_RIGHTMOVECIRCLE;

		}
		else if (_fPosX < WINSIZEX / 2 && _fAngle == PI)
		{
			_fCircleCenterX = WINSIZEX / 2;
			_fCircleCenterY = _fPosY + 150.0f;
			_fAngle = PI / 2;
			_fPosX = WINSIZEX / 2;
			_eMovePhase = C_SMOKE::E_MOVEPHASE::E_LEFTMOVECIRCLE;
		}
	}
	else if (_eMovePhase == C_SMOKE::E_MOVEPHASE::E_LEFTMOVECIRCLE)
	{
		_fAngle += 0.02f;
		_fPosX = _fCircleCenterX + Mins::presentPowerX(_fAngle, 150.0f);
		_fPosY = _fCircleCenterY + Mins::presentPowerY(_fAngle, 150.0f);
	}
	else if (_eMovePhase == C_SMOKE::E_MOVEPHASE::E_RIGHTMOVECIRCLE)
	{
		_fAngle -= 0.02f;
		_fPosX = _fCircleCenterX + Mins::presentPowerX(_fAngle, 150.0f);
		_fPosY = _fCircleCenterY + Mins::presentPowerY(_fAngle, 150.0f);
	}

	//충돌처리 삭제 만들어야한다.
	//그럼 블릿 매니저를 알아야하네?

	if (_eMovePhase == C_SMOKE::E_MOVEPHASE::E_RIGHTMOVECIRCLE || _eMovePhase == C_SMOKE::E_MOVEPHASE::E_LEFTMOVECIRCLE)
	{
		if (_fAngle < PI + PI / 2.0f + 0.01f && _fAngle > PI + PI / 2.0f - 0.01f)
		{
			_nCircleCycleCount++;
		}
	}

	//앵글을 0~PI2사이값으로 한다
	if (_fAngle < 0)
	{
		_fAngle = PI2 - _fAngle;
	}
	else if (_fAngle > PI2)
	{
		_fAngle = _fAngle - PI2;
	}

	//삭제
	if (_nCircleCycleCount > 5)
	{
		_bIsRemove = true;
	}

	//애니메이션 상태처리
	_nAniFrameCount++;

	if (_nAniFrameCount % 5 == 0)
	{
		_nCurrentFrameX++;
		if (_nCurrentFrameX >= _pImg->getMaxFrameX())
		{
			_nCurrentFrameX = 0;
		}
		_nAniFrameCount = 0;
	}

	_nFireReloadCount++;
	if (_nFireReloadCount == C_SMOKE::E_RELOADTIME) {

		_bIsFire = true;
	}

}

void C_SMOKE::release()
{
	_pImg = nullptr;
}

void C_SMOKE::render(HDC hDc)
{
	_pImg->frameRenderCenter(hDc, static_cast<int>(_fPosX), static_cast<int>(_fPosY), _nCurrentFrameX, 0);
}

void C_SMOKE::fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)
{
	for (int i = 0; i < 36; i++)
	{
		pBulletMgr->fire(_fPosX, _fPosY, PI2 / 36.0f * static_cast<float>(i), 0, IMAGEMANAGER->findImage("colorBullet"), 3.0f, 10, 10, 18, false, C_BULLET::E_BULLETTYPE::E_STRIGHT);
	}
	_bIsFire = false;
	_nFireReloadCount = 0;

}

bool C_SMOKE::checkRemove()
{
	return _bIsRemove;
}

bool C_SMOKE::checkFireOk()
{
	return _bIsFire;
}

float C_SMOKE::getPosX()
{
	return _fPosX;
}

float C_SMOKE::getPosY()
{
	return _fPosY;
}

int C_SMOKE::getRadius()
{
	return _nWidth;
}

void C_SMOKE::damage(int nDamage)
{
	_nHp -= nDamage;
	if (_nHp <= 0)
	{
		_bIsRemove = true;
	}
}

int C_SMOKE::getHp()
{
	return _nHp;
}

int C_SMOKE::getItem()
{
	return 0;
}

bool C_SMOKE::bulletClear()
{
	return false;
}

