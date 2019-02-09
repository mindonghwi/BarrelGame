#include "stdafx.h"
#include "itemMgr.h"
#include "bulletMgr.h"
#include "player.h"
#include "enemyMgr.h"
#include "uimgr.h"
#include "effectMgr.h"
#include "powerUp.h"
#include "score.h"
#include "bomb.h"


C_ITEMMGR::C_ITEMMGR()
{
}

C_ITEMMGR::~C_ITEMMGR()
{
}

void C_ITEMMGR::init(int nMaxCount)
{
	_nMemPoolCount = nMaxCount;
	_vqItemPool.resize(3);
	
	//юс╫ц
	_vqItemPool[0] = new queue< I_ITEM*>();
	_vqItemPool[1] = new queue< I_ITEM*>();
	_vqItemPool[2] = new queue< I_ITEM*>();


	queue< I_ITEM*> qItem[static_cast<int>(I_ITEM::E_ITEMTYPE::E_MAX)];
	for (int i = 0; i < 3000; i++)
	{
		I_ITEM* pItem;
		pItem = new C_POWERUP();
		pItem->init();
		//qItem[static_cast<int>(I_ITEM::E_ITEMTYPE::E_POWER)].push(pItem);
		_vqItemPool[static_cast<int>(I_ITEM::E_ITEMTYPE::E_POWER)]->push(pItem);
	}
	for (int i = 0; i < 1000; i++)
	{
		I_ITEM* pItem;
		pItem = new C_BOMB();
		pItem->init();
		//qItem[static_cast<int>(I_ITEM::E_ITEMTYPE::E_BOMB)].push(pItem);
		_vqItemPool[static_cast<int>(I_ITEM::E_ITEMTYPE::E_BOMB)]->push(pItem);

	}
	for (int i = 0; i < 4000; i++)
	{
		I_ITEM* pItem;
		pItem = new C_SCORE();
		pItem->init();
		//qItem[static_cast<int>(I_ITEM::E_ITEMTYPE::E_SCORE)].push(pItem);
		_vqItemPool[static_cast<int>(I_ITEM::E_ITEMTYPE::E_SCORE)]->push(pItem);

	}

	//for (int i = 0; i < static_cast<int>(I_ITEM::E_ITEMTYPE::E_MAX); i++)
	//{
	//	_vqItemPool.push_back(qItem[i]);
	//}
	_bISDrain = false;
}

void C_ITEMMGR::update()
{

	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		_bISDrain = true;
	}
	if (_listItemAlive.empty())
	{
		_bISDrain = false;
	}


	list<I_ITEM*>::iterator end = _listItemAlive.end();
	list<I_ITEM*>::iterator itor = _listItemAlive.begin();

	while (itor != end)
	{
		I_ITEM* pItem = *itor;
		pItem->update();
		if (_bISDrain)
		{
			pItem->setDrain(_pPlayer->getPosX(), _pPlayer->getPosY());
		}



		if (onCollision(_pPlayer->getPosX(),_pPlayer->getPosY(),_pPlayer->getWidth(),_pPlayer->getHeight(),pItem)
			|| pItem->getPosY() - pItem->getHeight()/2 > WINSIZEY)
		{
			if (pItem->getPosY() - pItem->getHeight() / 2 < WINSIZEY)
			{
				if (pItem->getItemType() == I_ITEM::E_ITEMTYPE::E_POWER)
				{
					_pPlayer->addPower(pItem->getPoint());
				}
				if (pItem->getItemType() == I_ITEM::E_ITEMTYPE::E_BOMB)
				{
					_pPlayer->addSpell(pItem->getPoint());
				}
				if (pItem->getItemType() == I_ITEM::E_ITEMTYPE::E_SCORE)
				{
					_pPlayer->addScore(pItem->getPoint());
				}
			}


			_vqItemPool[static_cast<int>(pItem->getItemType())]->push(pItem);
			pItem->release();
			itor = _listItemAlive.erase(itor);
		}
		else {
			itor++;
		}
	}
}

void C_ITEMMGR::release()
{
	list<I_ITEM*>::iterator end = _listItemAlive.end();
	list<I_ITEM*>::iterator itor = _listItemAlive.begin();

	while (itor != end)
	{
		I_ITEM* pItem = *itor;
		pItem->release();
		itor = _listItemAlive.erase(itor);
		delete pItem;
		pItem = nullptr;
		itor++;
	}

	for (int i = 0; i < static_cast<int>(I_ITEM::E_ITEMTYPE::E_MAX); i++)
	{
		while (!_vqItemPool[i]->empty())
		{
			I_ITEM* pItem = _vqItemPool[i]->front();
			pItem->release();
			_vqItemPool[i]->pop();
			
			delete pItem;
			pItem = nullptr;
		}
		//
		delete _vqItemPool[i];
		_vqItemPool[i] = nullptr;
	}

}

void C_ITEMMGR::render(HDC hdc)
{
	list<I_ITEM*>::iterator end = _listItemAlive.end();
	list<I_ITEM*>::iterator itor = _listItemAlive.begin();

	while (itor != end)
	{
		I_ITEM* pItem = *itor;
		pItem->render(hdc);
		itor++;
	}
}

void C_ITEMMGR::createItem(float fPosX, float fPosY, I_ITEM::E_ITEMTYPE eItem)
{
	
	if (eItem == I_ITEM::E_ITEMTYPE::E_MAX)
	{
		return;	
	}	
	if (_vqItemPool[static_cast<int>(eItem)]->empty())
	{
		return;
	}

	I_ITEM* pItem;
	pItem = _vqItemPool[static_cast<int>(eItem)]->front();
	pItem->create(fPosX, fPosY, eItem);
	_listItemAlive.push_back(pItem);
	_vqItemPool[static_cast<int>(eItem)]->pop();
}

bool C_ITEMMGR::onCollision(float fPosX, float fPosY, int nWidth, int nHeight, I_ITEM* pITem)
{
	RECT rcTmp;
	RECT rcDst;
	RECT rcSrc;
	rcDst = RectMakeCenter(fPosX, fPosY, nWidth, nHeight);
	rcSrc = RectMakeCenter(pITem->getPosX(), pITem->getPosY(), pITem->getWidth(), pITem->getHeight());

	if (IntersectRect(&rcTmp ,&rcDst, &rcSrc))
	{
		return true;
	}
	
	return false;

}
