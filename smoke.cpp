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
	//�����Ҷ� 
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
	//�����̵�
	//���
	// ----------
	//       /   \
	//       \   /
	//�̵�
	if (_eMovePhase == C_SMOKE::E_MOVEPHASE::E_STRIGHT)
	{
		_fPosX += Mins::presentPowerX(_fAngle, _fSpeed);
		_fPosY += Mins::presentPowerY(_fAngle, _fSpeed);

		//� �ٲٱ�
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

	//�浹ó�� ���� �������Ѵ�.
	//�׷� �� �Ŵ����� �˾ƾ��ϳ�?

	if (_eMovePhase == C_SMOKE::E_MOVEPHASE::E_RIGHTMOVECIRCLE || _eMovePhase == C_SMOKE::E_MOVEPHASE::E_LEFTMOVECIRCLE)
	{
		if (_fAngle < PI + PI / 2.0f + 0.01f && _fAngle > PI + PI / 2.0f - 0.01f)
		{
			_nCircleCycleCount++;
		}
	}

	//�ޱ��� 0~PI2���̰����� �Ѵ�
	if (_fAngle < 0)
	{
		_fAngle = PI2 - _fAngle;
	}
	else if (_fAngle > PI2)
	{
		_fAngle = _fAngle - PI2;
	}

	//����
	if (_nCircleCycleCount > 5)
	{
		_bIsRemove = true;
	}

	//�ִϸ��̼� ����ó��
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

