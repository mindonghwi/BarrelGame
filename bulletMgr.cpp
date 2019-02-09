#include "stdafx.h"
#include "bulletMgr.h"
#include "enemyMgr.h"
#include "effectMgr.h"
//#include "uimgr.h"
#include "itemMgr.h"

C_BULLETMGR::C_BULLETMGR():
	_nPoolCount(0),
	_pPlayer(nullptr)
{
}

C_BULLETMGR::~C_BULLETMGR()
{
}

void C_BULLETMGR::init(int nPoolCount)
{
	_nPoolCount = nPoolCount;
	setMemPool();
	
}

void C_BULLETMGR::update()
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();

	for (; itor != end;)
	{
		C_BULLET* pBullet;
		pBullet = *itor;
		pBullet->update();


		if (pBullet->checkOutBullet())
		{
			pBullet->deleteBullet();
			_queMemPoolBullet.push(pBullet);
			itor = _listAliveBullet.erase(itor);
		}
		else {
			itor++;
		}
	}

	findNearEnemy();
}

void C_BULLETMGR::release()
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();
	
	while (itor != end)
	{
		C_BULLET* pBullet = *itor;
		pBullet->release();
		itor = _listAliveBullet.erase(itor);
		delete pBullet;
		pBullet = nullptr;
	}

	while (!_queMemPoolBullet.empty())
	{
		C_BULLET* pBullet = _queMemPoolBullet.front();
		pBullet->release();
		_queMemPoolBullet.pop();
		delete pBullet;
		pBullet = nullptr;
	}

}

void C_BULLETMGR::render()
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();

	for (; itor != end; itor++)
	{
		C_BULLET* pBullet;
		pBullet = *itor;
		pBullet->render();
	}


}

void C_BULLETMGR::setPlayer(C_PLAYER * pPlayer)
{
	_pPlayer = pPlayer;
}

bool C_BULLETMGR::onPlayerCollsion(float fPosX, float fPosY, float fRadius)
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();

	for (; itor != end;)
	{
		C_BULLET* pBullet;
		pBullet = *itor;

		if (!pBullet->getIsPlayer() && Mins::IsCollisionCirtoCir((int)fPosX, (int)fPosY, (int)fRadius, (int)pBullet->getPosX(), (int)pBullet->getPoSY(), (int)pBullet->getRadius()/2))
		{
			pBullet->deleteBullet();
			_queMemPoolBullet.push(pBullet);
			itor = _listAliveBullet.erase(itor);
			return true;
		}
		else {
			itor++;
		}
	}

	return false;
}

int C_BULLETMGR::onEnemyCollsion(float fPosX, float fPosY, int nWidth, int nHeight)
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();
	int	nIndex = 0;
	int nDamage = 0;
	for (; itor != end;)
	{
		C_BULLET* pBullet;
		pBullet = *itor;

		if (pBullet->getIsPlayer() && Mins::IsCollisionCirtoCir((int)fPosX, (int)fPosY, (int)nWidth/2, (int)pBullet->getPosX(), (int)pBullet->getPoSY(), (int)pBullet->getRadius()))
		{
			if (pBullet->getBullType() != C_BULLET::E_BULLETTYPE::E_SPELL)
			{
				pBullet->deleteBullet();
				_queMemPoolBullet.push(pBullet);
				itor = _listAliveBullet.erase(itor);
			}
			nDamage += pBullet->getDamage();
		}
		else {
			itor++;
			nIndex++;
		}
	}

	return nDamage;
}

bool C_BULLETMGR::getNotEnemyBullet()
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();

	for (; itor != end; itor++)
	{
		C_BULLET* pBullet;
		pBullet = *itor;
		if (!pBullet->getIsPlayer())
		{
			return false;
		}
	}

	return true;
}

void C_BULLETMGR::clearBullet()
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();

	for (; itor != end;)
	{
		C_BULLET* pBullet;
		pBullet = *itor;

		if (!pBullet->getIsPlayer())
		{
			float fPosX = pBullet->getPosX();
			float fPosY = pBullet->getPoSY();

			_pEffectMgr->createEffect(fPosX, fPosY, "num1000");
			_pPlayer->addScore(1000);

			_pEffectMgr->createEffect(fPosX, fPosY, "bulletDeleteEffect");
			_pItemMgr->createItem(fPosX, fPosY, I_ITEM::E_ITEMTYPE::E_SCORE);
			pBullet->deleteBullet();
			_queMemPoolBullet.push(pBullet);
			itor = _listAliveBullet.erase(itor);
		}
		else
			itor++;

	}
}

void C_BULLETMGR::setDamage(int nDamage)
{
	C_BULLET* pBullet = _listAliveBullet.back();
	pBullet->setDamage(nDamage);
	
}

void C_BULLETMGR::goHurricane()
{
	list<C_BULLET*>::iterator itor = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();

	for (; itor != end;itor++)
	{
		C_BULLET* pBullet;
		pBullet = *itor;
		
		if (pBullet->getBullType() == C_BULLET::E_BULLETTYPE::E_STRIGHTSLOW
			|| pBullet->getBullType() == C_BULLET::E_BULLETTYPE::E_STRIGHT 
			|| pBullet->getBullType() == C_BULLET::E_BULLETTYPE::E_SPELL
			|| pBullet->getBullType() == C_BULLET::E_BULLETTYPE::E_HOMING)
		{
			
		}
		else {
			if (pBullet->getBullType() != C_BULLET::E_BULLETTYPE::E_STRIGHTSLOW)
			{
				pBullet->setfSpeed(RND->getFromFloatTo(3.0f, 5.0f));
				pBullet->setRndAngle();
				pBullet->setBullType(C_BULLET::E_BULLETTYPE::E_STRIGHT);
			}
		}

	}

}

void C_BULLETMGR::setfSpeed(float fSpeed)
{
	C_BULLET* pBullet = _listAliveBullet.back();
	pBullet->setfSpeed(fSpeed);
}

void C_BULLETMGR::setLimitedRadius(float fRadius)
{
	C_BULLET* pBullet = _listAliveBullet.back();
	pBullet->setLimitedRadius(fRadius);
}

void C_BULLETMGR::setBottomRadius(float fRadius)
{
	C_BULLET* pBullet = _listAliveBullet.back();
	pBullet->setBottomRadius(fRadius);
}

void C_BULLETMGR::setCircleX(float fX)
{
	C_BULLET* pBullet = _listAliveBullet.back();
	pBullet->setCircleX(fX);
}

void C_BULLETMGR::setCircleY(float fY)
{
	C_BULLET* pBullet = _listAliveBullet.back();
	pBullet->setCircleY(fY);
}


void C_BULLETMGR::setMemPool()
{
	for (int i = 0; i < _nPoolCount; i++)
	{
		C_BULLET* pBullet;
		pBullet = new C_BULLET();
		pBullet->init();

		_queMemPoolBullet.push(pBullet);
	}
}

bool C_BULLETMGR::fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool bIsPlayers, C_BULLET::E_BULLETTYPE eBullet)
{
	if (_queMemPoolBullet.empty())
	{
		return false;
	}

	C_BULLET* pBullet(nullptr);

	pBullet = _queMemPoolBullet.front();
	
	pBullet->fire(fPosX, fPosY, fUnitAngle, fRotateAngle, pImg, fSpeed, nCollisionWidth, nCollisionHeight, nMaxFrame, bIsPlayers, eBullet);
	_listAliveBullet.push_back(pBullet);
	_queMemPoolBullet.pop();

	return true;
}

bool C_BULLETMGR::fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool bIsPlayers, C_BULLET::E_BULLETTYPE eBullet, int nStopFrame)
{
	if (_queMemPoolBullet.empty())
	{
		return false;
	}

	C_BULLET* pBullet(nullptr);

	pBullet = _queMemPoolBullet.front();

	pBullet->fire(fPosX, fPosY, fUnitAngle, fRotateAngle, pImg, fSpeed, nCollisionWidth, nCollisionHeight, nMaxFrame, bIsPlayers, eBullet, nStopFrame);
	_listAliveBullet.push_back(pBullet);
	_queMemPoolBullet.pop();

	return true;
}

bool C_BULLETMGR::fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType, float fRange)
{
	if (_queMemPoolBullet.empty())
	{
		return false;
	}

	C_BULLET* pBullet(nullptr);

	pBullet = _queMemPoolBullet.front();

	pBullet->fire(fPosX, fPosY, fUnitAngle, fRotateAngle, pImg, fSpeed, nCollisionWidth, nCollisionHeight, nMaxFrame, bIsPlayers, eBulletType, fRange);
	_listAliveBullet.push_back(pBullet);
	_queMemPoolBullet.pop();

	return true;
}


void C_BULLETMGR::setFrameY(int nIndex)
{
	_listAliveBullet.back()->setFraneY(nIndex);

}

void C_BULLETMGR::serFrameX(int nIndex)
{
	_listAliveBullet.back()->setFraneX(nIndex);

}

void C_BULLETMGR::findNearEnemy()
{
	list<C_BULLET*>::iterator itorl = _listAliveBullet.begin();
	list<C_BULLET*>::iterator end = _listAliveBullet.end();
	for (;itorl != end; itorl++)
	{
		for (int i = 0; i < _pEnemyMgr->getEnemySize(); i++)
		{
			C_BULLET* pBullet = *itorl;
			if (pBullet->getBullType() == C_BULLET::E_BULLETTYPE::E_HOMING && pBullet->getIsPlayer())
			{
				pBullet->findAngleEnemy(_pEnemyMgr->getEnemyPosX(i), _pEnemyMgr->getEnemyPosY(i));
			}
		}
		
	}
}

