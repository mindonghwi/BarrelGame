#include "stdafx.h"
#include "bullet.h"

C_BULLET::C_BULLET():
	_fPosX			 (0.0f),
	_fPosY			 (0.0f),
	_nWidth			 (0),
	_nHeight		 (0),
	_fUnitVectorAngle(0.0f),
	_fRotateAngle	 (0.0f),
	_fSpeed			 (0.0f),
	_pImg			 (nullptr),
	_nCollisionWidth (0),
	_nCollisionHeight(0),
	_nCurrentFrame(0),
	_nMaxFrame(0),
	_bIsPlayerBullet(false),
	_eBulletType(C_BULLET::E_BULLETTYPE::E_NONE)
{
}

C_BULLET::~C_BULLET()
{
}


HRESULT C_BULLET::init()
{
	_fPosX = -2000.0f;
	_fPosY = -2000.0f;
	_fUnitVectorAngle = 0.0f;
	_fRotateAngle = 0.0f;
	_pImg = nullptr;
	_fSpeed = 0.0f;
	_nCollisionHeight = 0;
	_nCollisionWidth = 0;
	_nWidth = 0;
	_nHeight = 0;
	_nCurrentFrame = 0;
	_nMaxFrame = 0;
	_bIsPlayerBullet = false;
	_eBulletType = C_BULLET::E_BULLETTYPE::E_NONE;
	return S_OK;
}

void C_BULLET::release()
{
	_pImg = nullptr;
}

void C_BULLET::update()
{
	if (_eBulletType == C_BULLET::E_BULLETTYPE::E_STRIGHT)
	{
		moveStraight();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_HOMING)
	{
		moveHoming();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_WAVE)
	{
		moveWave();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_DELEYTURN)
	{
		moveDeleyTurn();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_CHASINGSHOT) 
	{
		chargingShot();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_MOVEDELEYRANDOM)
	{
		moveDeleyRanDom();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_LAZER)
	{
		moveLazer();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_SPELL) 
	{
		moveSpell();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_HERICAIN) 
	{
		moveHericain();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_SLIDER)
	{
		moveNotTimeSlider();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_LEAFSTORM)
	{
		moveLeafStorm();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_STRIGHTSLOW)
	{
		moveSlow();
	}
	else if (_eBulletType== C_BULLET::E_BULLETTYPE::E_TRUETRI)
	{
		moveTrueTri();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_INVERSETRI)
	{
		moveInverseTri();
	}
	else if (_eBulletType == C_BULLET::E_BULLETTYPE::E_CIRCLE)
	{
		moveCircle();
	}


	setFrame();
}

void C_BULLET::render()
{
	//RectangleMakeCenter(getMemDC(), _fPosX, _fPosY, 20, 52);

	if (_bIsPlayerBullet)
	{
		_pImg->alphaFrameRender(getMemDC(), (int)_fPosX - _nWidth / 2, (int)_fPosY - _nHeight / 2, _nCurrentFrame, _nCurrentFrameY,150);

	}
	else {
		_pImg->frameRender(getMemDC(), (int)_fPosX - _nWidth / 2, (int)_fPosY - _nHeight / 2, _nCurrentFrame, _nCurrentFrameY);

	}
}

//x좌표 y좌표, 단위각도, 회전각도, 이미지, 스피드, 충돌가로길이,충돌세로길이,총 프레임의 수(1~)
void C_BULLET::fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool _bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType)
{
	_fPosX = fPosX;
	_fPosY = fPosY;
	_fUnitVectorAngle = fUnitAngle;
	_fRotateAngle = fRotateAngle;
	_pImg = pImg;
	_fSpeed = fSpeed;
	_nCollisionHeight = nCollisionHeight;
	_nCollisionWidth = nCollisionWidth;
	_nWidth = pImg->getFrameWidth();
	_nHeight = pImg->getFrameHeight();
	_nMaxFrame = nMaxFrame;
	_bIsPlayerBullet = _bIsPlayers;
	_eBulletType = eBulletType;
	_nAttacking = 10;

	_fWavePosX = _fPosX;
	_fWavePosY = _fPosY;
	_nCurrentFrameY = 0;
	_fDis =10000000.0f;

	_fStartX = fPosX;
	_fStartY = fPosY;
	_nTurnPower = -1;
	_bIsRemove = false;
}

void C_BULLET::fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool _bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType, int nStopFrame)
{
	fire( fPosX,  fPosY,  fUnitAngle,  fRotateAngle, pImg,  fSpeed,  nCollisionWidth,  nCollisionHeight,  nMaxFrame,  _bIsPlayers,  eBulletType);
	_nStopFrame = nStopFrame;
	_nKeepFlowerFrame = _nStopFrame;
}

void C_BULLET::fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool _bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType, float fRange)
{
	fire(fPosX, fPosY, fUnitAngle, fRotateAngle, pImg, fSpeed, nCollisionWidth, nCollisionHeight, nMaxFrame, _bIsPlayers, eBulletType);
	_fRange = fRange;
}

void C_BULLET::findAngleEnemy(float fPosX, float fPosY)
{
	float fDis = Mins::getDoubleDistance(fPosX, fPosY, _fPosX, _fPosY);
	if (fDis < _fDis)
	{
		_fUnitVectorAngle = getAngle(_fPosX, _fPosY, fPosX, fPosY);
		_fDis = fDis;
	}

}

void C_BULLET::setFraneY(int nIndex)
{
	_nCurrentFrameY = nIndex;
}

void C_BULLET::setFraneX(int nIndex)
{
	_nCurrentFrame = nIndex;
}


void C_BULLET::moveStraight()
{
	_fPosX += cosf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
	_fPosY += -sinf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
}

void C_BULLET::moveHoming()
{

	_fPosX += cosf(_fUnitVectorAngle) * _fSpeed;
	_fPosY += -sinf(_fUnitVectorAngle) * _fSpeed;

}

void C_BULLET::moveWave()
{
	_fWavePosX += cosf(_fUnitVectorAngle) * _fSpeed;
	_fWavePosY += -sinf(_fUnitVectorAngle) * _fSpeed;

	_fPosX = _fWavePosX + sinf(_fRotateAngle)* 30.0f;
	_fPosY = _fWavePosY + sinf(_fRotateAngle)* 30.0f;

	_fRotateAngle += PI2/36.0f;
	if (fabsf(_fRotateAngle - PI2) <= FLT_EPSILON)
	{
		_fRotateAngle = _fRotateAngle - PI2;
	}
}

void C_BULLET::moveDeleyTurn()
{
	float	fDisX = _fPosX - _fStartX;
	float	fDisY = _fPosY - _fStartY;


	if (_fRange < fDisX * fDisX + fDisY * fDisY)
	{
		//if (RND->getInt(1) == 0) {
		//	_fRotateAngle += PI / 2;
		//}
		//else {
		//	_fRotateAngle -= PI / 2;
		//}
		_fSpeed = 3.5f;
	}
	_fPosX += cosf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
	_fPosY += -sinf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
}

void C_BULLET::chargingShot()
{
	if (_nStopFrame > 0)
	{
		_fRotateAngle += RND->getFloat(3.0f);
		_nStopFrame--;
	}
	else {
		_fSpeed = 12.0f;
		moveStraight();
	}
}

void C_BULLET::moveDeleyRanDom()
{
	if (_nKeepFlowerFrame > 0)
	{
		_nKeepFlowerFrame--;
		
	}
	else if (_nKeepFlowerFrame == 0)
	{
		_fRotateAngle = RND->getFloat(PI2);
		_nCurrentFrame = RND->getInt(6);
		_nKeepFlowerFrame--;
	}

	_fPosX += cosf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
	_fPosY += -sinf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
}

void C_BULLET::moveLazer()
{
	float	fDisX = _fPosX - _fStartX;
	float	fDisY = _fPosY - _fStartY;


	if (_fRange < fDisX * fDisX + fDisY * fDisY)
	{
		_bIsRemove = true;
	}
	_fPosX += cosf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;
	_fPosY += -sinf(_fUnitVectorAngle + _fRotateAngle) * _fSpeed;

}

void C_BULLET::moveSpell()
{
	_fPosX += cosf(_fRotateAngle) * _fSpeed*2.0f;
	_fPosY += -sinf(_fUnitVectorAngle) * _fSpeed;


	_fRotateAngle += PI/18.0f;

}

void C_BULLET::moveHericain()
{
	_fPosX =_fStartX +  Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY =_fStartY +  Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	if (_fSpeed < 200)
	{
		_fSpeed += 2.1f;
	}
	if (_fRotateAngle < 0)
	{
		_fRotateAngle -= PI / 180.0f;
	}
	else {
		_fRotateAngle += PI / 180.0f;
	}

}

void C_BULLET::moveNotTimeSlider()
{
	_fPosX += Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY += Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	_fRotateAngle += PI / 18.0f;
	//_fSpeed += 1.0f;

}

void C_BULLET::moveLeafStorm()
{
	_fPosX += Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY += Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	_fRotateAngle += PI / 18.0f;
	_fSpeed += (float)_nTurnPower * 0.2f;

	if (_fSpeed <= _fBottomRaddius)
	{
		_nTurnPower *= -1;
	}
	else if (_fSpeed >= _fLimitedRadius)
	{
		_nTurnPower *= -1;
	}


}

void C_BULLET::moveSlow()
{
	_fPosX += Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY += Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	if (_fSpeed >= _fBottomRaddius)
	{
		_fSpeed -= 1.9f;
	}
}

void C_BULLET::moveTrueTri()
{
	_fPosX += Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY += Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	if (Mins::getDoubleDis(_fPosX , _fPosY,_fSavePosX,_fSavePosY) >= _fLimitedRadius * _fLimitedRadius)
	{
		_fUnitVectorAngle -= PI / 3.0f;
	}
}

void C_BULLET::moveInverseTri()
{
	_fPosX += Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY += Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	if (Mins::getDoubleDis(_fPosX, _fPosY, _fSavePosX, _fSavePosY) >= _fLimitedRadius * _fLimitedRadius)
	{
		_fUnitVectorAngle += PI + PI / 3.0f;
	}
}

void C_BULLET::moveCircle()
{
	_fPosX = _fSavePosX +  Mins::presentPowerX(_fUnitVectorAngle + _fRotateAngle, _fSpeed);
	_fPosY = _fSavePosY +  Mins::presentPowerY(_fUnitVectorAngle + _fRotateAngle, _fSpeed);

	_fRotateAngle += PI / 130.0f;
}

void C_BULLET::setFrame()
{
	float	fAngle = _fUnitVectorAngle + _fRotateAngle;

	if (fAngle > PI2)
	{
		fAngle -= PI2;
	}
	else if (fAngle < 0)
	{
		fAngle = PI2 + fAngle;
	}

	if (_nMaxFrame == 1)
	{

	}
	else if (_nMaxFrame < 19)
	{
		_nCurrentFrame = Mins::getNearAngleSBullet(fAngle);

	}
	else {
		_nCurrentFrame = Mins::getNearAnglePI2(fAngle);
	}
}

bool C_BULLET::checkOutBullet()
{
	
	if (_fPosX + _nWidth/2 <= 0 ||
		_fPosX - _nWidth / 2 >= WINSIZEX ||
		_fPosY + _nHeight / 2 <= 0 ||
		_fPosY - _nHeight / 2 >= WINSIZEY)
	{
		if (_eBulletType != C_BULLET::E_BULLETTYPE::E_LAZER )
		{
			_bIsRemove = true;
		}
		if (_eBulletType == C_BULLET::E_BULLETTYPE::E_HERICAIN)
		{
			_bIsRemove = false;

		}
	}

	//if (_eBulletType == C_BULLET::E_BULLETTYPE::E_SPELL &&
	//(_fPosX - _nWidth / 2 >= WINSIZEX ||
	//	_fPosY + _nHeight / 2 <= 0 ||
	//	_fPosY - _nHeight / 2 >= WINSIZEY))
	//{
	//	_bIsRemove = false;
	//}

	return _bIsRemove;
}

void C_BULLET::deleteBullet()
{
	_fPosX = -2000.0f;
	_fPosY = -2000.0f;
	_fUnitVectorAngle = 0.0f;
	_fRotateAngle = 0.0f;
	_pImg = nullptr;
	_fSpeed = 0.0f;
	_nCollisionHeight = 0;
	_nCollisionWidth = 0;
	_nWidth = 0;
	_nHeight = 0;
	_nCurrentFrame = 0;
	_nMaxFrame = 0;
}
