#include "stdafx.h"
#include "enemyMgr.h"
#include "effectMgr.h"

#include "bulletMgr.h"
#include "player.h"
#include "uimgr.h"
#include "itemMgr.h"


C_ENEMYMGR::C_ENEMYMGR():
	_nFrameCount(0),
	_nBIsNextStage(false)
{
}

C_ENEMYMGR::~C_ENEMYMGR()
{
}

HRESULT C_ENEMYMGR::init()
{
	_vEnemy.reserve(30);

	_nBIsNextStage = true;
	_nFrameCount = 0;
	_bISLastBoss = false;
	return S_OK;
}

void C_ENEMYMGR::update()
{
	//생성되어있는 에네미 업데잍트 돌리기
	/*vector<I_ENEMY*>::iterator	itorEnd = _vEnemy.end();
	_vitorEnemy = _vEnemy.begin();
	for (; _vitorEnemy != itorEnd; )
	{
		I_ENEMY* pEnemy;
		pEnemy = *_vitorEnemy;
		pEnemy->update();
		if (pEnemy->checkRemove())
		{
			pEnemy->release();
			
			_vitorEnemy = _vEnemy.erase(_vitorEnemy);
			
		}
		else
		{
			_vitorEnemy++;
		}
	}*/
	
	for (int i = 0; i <_vEnemy.size();i++)
	{
		I_ENEMY* pEnemy;
		pEnemy = _vEnemy[i];
		pEnemy->update();
		if (pEnemy->checkFireOk())
		{
			pEnemy->fire(_pBulletMgr, _pPlayer);
		}

		if (pEnemy->checkRemove())
		{
			float	fPosX = pEnemy->getPosX();
			float	fPosY = pEnemy->getPosY();

			

			_pEffectMgr->createEffect(fPosX, fPosY, "enemyEffectDeath");

			_pItemMgr->createItem(fPosX, fPosY,static_cast<I_ITEM::E_ITEMTYPE>(pEnemy->getItem()));



			pEnemy->release();
			
			//_vEnemy[i] = nullptr;
			_vEnemy.erase(_vEnemy.begin()+ i);
			delete pEnemy;
			pEnemy = nullptr;
			i--;
		}	
	}

	//몬스터 등장 처리
	
	if (_nBIsNextStage)
	{
		_nFrameCount++;
	}

	if (_nFrameCount == 30)
	{
		for (int i = 0; i < 6; i++)
		{
			createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_FLORA, 100.0,static_cast<float>(WINSIZEY + i * 40), PI / 2, 2.0f);
			createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_FLORA, static_cast<float>(WINSIZEX - 100), static_cast<float>(WINSIZEY + i * 40), PI / 2, 2.0f);
		}
		_nBIsNextStage = false;
		_nFrameCount ++;

	}

	if (_nFrameCount == 60)
	{
		for (int i = 0; i < 6; i++)
		{
			createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_FLORA, 100.0, static_cast<float>(0 - i * 40), PI / 2+ PI, 4.0f - (float)i * 0.4f);
			createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_FLORA, static_cast<float>(WINSIZEX - 100), static_cast<float>(0 - i * 40), PI / 2 + PI, 4.0f - (float)i * 0.4f);
		}

		for (int i = 0; i < 6; i++)
		{
			createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_SMOKE, 0 - i * 60, 150.0f, 0, 4.0f);
			createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_SMOKE, WINSIZEX + i * 60, 200.0f, PI, 4.0f);
		}
		_nBIsNextStage = false;
		_nFrameCount++;
	}

	if (_nFrameCount == 90)
	{
		createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_FAIRY, 0, -30.0f, PI2 - PI / 4.0f, 4.0f);
		createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_FAIRY, WINSIZEX / 2.0f, -30.0f, PI2 - PI / 4.0f, 4.0f);
		_nBIsNextStage = false;
		_nFrameCount++;

	}

	if (_nFrameCount == 180)
	{
		createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_BOSS, WINSIZEX/2.0f, -30.0f, PI2 - PI/2.0f, 4.0f);
		_nBIsNextStage = false;
		_nFrameCount++;
	}

	if (_nFrameCount == 250)
	{
		createEnemy(C_ENEMYMGR::E_ENEMYTYPE::E_LASTBOSS, WINSIZEX / 2.0f, -30.0f, PI2 - PI / 2.0f, 4.0f);
		_nBIsNextStage = false;
		_nFrameCount++;
	}


	//몬스터가 다 사라졌으면
	if (_vEnemy.empty() && _nBIsNextStage == false)
	{
		_nBIsNextStage = true;

		//남는거
		_pBulletMgr->clearBullet();

		if (_pUiMgr->gethpBar())
		{
			_pUiMgr->destoryHpBar();
		}

		if (_pUiMgr->getLBBar())
		{
			_pUiMgr->destoryLbUI();
		}
	}

	if (_nFrameCount >= 300 && _pItemMgr->getListCount() == 0)
	{
		_bISGameEnd = true;
	}

	onEnemyCollision();
}

void C_ENEMYMGR::render()
{
	vector<I_ENEMY*>::iterator	itorEnd = _vEnemy.end();
	for (_vitorEnemy = _vEnemy.begin(); _vitorEnemy != itorEnd; _vitorEnemy++)
	{
		I_ENEMY* pEnemy;
		pEnemy = *_vitorEnemy;
		pEnemy->render(getMemDC());
	}
}

void C_ENEMYMGR::release()
{
	_pBulletMgr = nullptr;
	_pPlayer = nullptr;
	_pEffectMgr = nullptr;
	_pUiMgr = nullptr;
	_pItemMgr = nullptr;
	for (int i = 0; i < (int)_vEnemy.size(); i++)
	{
		I_ENEMY* pEnemy = _vEnemy[i];
		pEnemy->release();
		delete pEnemy;
		pEnemy = nullptr;
	}
	_vEnemy.clear();
}

void C_ENEMYMGR::createEnemy(E_ENEMYTYPE eEnemyType, float fPosX, float fPosY, float fAngle, float fSpeed)
{
	if (eEnemyType == C_ENEMYMGR::E_ENEMYTYPE::E_FLORA)
	{
		I_ENEMY* pEnemy;
		pEnemy = new C_FLORA();
		pEnemy->create(fPosX, fPosY, fAngle, fSpeed);
		_vEnemy.push_back(pEnemy);
	}
	else if (eEnemyType == C_ENEMYMGR::E_ENEMYTYPE::E_SMOKE)
	{
		I_ENEMY* pEnemy;
		pEnemy = new C_SMOKE();
		pEnemy->create(fPosX, fPosY, fAngle, fSpeed);
		_vEnemy.push_back(pEnemy);
	}
	else if (eEnemyType == C_ENEMYMGR::E_ENEMYTYPE::E_FAIRY)
	{
		I_ENEMY* pEnemy;
		pEnemy = new C_FAIRY();
		pEnemy->create(fPosX, fPosY, fAngle, fSpeed);
		_vEnemy.push_back(pEnemy);
	}
	else if (eEnemyType == C_ENEMYMGR::E_ENEMYTYPE::E_BOSS)
	{
		I_ENEMY* pEnemy;
		pEnemy = new C_BOSS();
		pEnemy->create(fPosX, fPosY, fAngle, fSpeed);
		_vEnemy.push_back(pEnemy);
		_pUiMgr->createHpBar();
		_pUiMgr->setNomalizeDamage(pEnemy->getHp());
	}
	else if (eEnemyType == C_ENEMYMGR::E_ENEMYTYPE::E_LASTBOSS)
	{
		I_ENEMY* pEnemy;
		pEnemy = new C_LASTBOSS();
		pEnemy->create(fPosX, fPosY, fAngle, fSpeed);
		_vEnemy.push_back(pEnemy);
		//_pUiMgr->createHpBar();
		//_pUiMgr->setNomalizeDamage(pEnemy->getHp());
		_bISLastBoss = true;
		_pUiMgr->createLbUI();
		_pUiMgr->setNomalizeDamageLb(pEnemy->getHp());
	}
}

void C_ENEMYMGR::onEnemyCollision()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{


		int nDamage = _pBulletMgr->onEnemyCollsion(_vEnemy[i]->getPosX(), _vEnemy[i]->getPosY(), _vEnemy[i]->getRadius(), _vEnemy[i]->getRadius());
		_pPlayer->addScore(nDamage);
		_vEnemy[i]->damage(nDamage);

		if (_bISLastBoss && _vEnemy[i]->bulletClear())
		{
			_pBulletMgr->clearBullet();
			_pUiMgr->returnBar();
		}

		if (_pUiMgr->gethpBar())
		{
			_pUiMgr->setDamage(nDamage);
		}

		if (_bISLastBoss)
		{
			_pUiMgr->setDamageLb(nDamage);
		}
	}


}
