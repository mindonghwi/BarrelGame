#include "stdafx.h"
#include "uimgr.h"
#include "hpBar.h"
#include "enemyMgr.h"
#include "player.h"

C_UIMGR::C_UIMGR()
{
}

C_UIMGR::~C_UIMGR()
{
}

void C_UIMGR::init()
{
}

void C_UIMGR::update()
{
	if (_pHpBar)
	{
		_pHpBar->update();
	}

	if (_pLBBar)
	{
		_pLBBar->update();
	}
	_vScore = _pPlayer->getScores();
}

void C_UIMGR::release()
{
	if (_pHpBar)
	{
		_pHpBar->release();
		delete _pHpBar;
		_pHpBar = nullptr;
	}
	if (_pLBBar)
	{
		_pLBBar->release();
		delete _pHpBar;
		_pLBBar = nullptr;
	}
	_vScore.clear();
}

void C_UIMGR::render(HDC hdc)
{
	if (_pHpBar)
	{
		_pHpBar->render();
	}
	if (_pLBBar)
	{
		_pLBBar->render();
	}

	IMAGEMANAGER->render("powerFont", hdc, WINSIZEX + 20, 50);
	IMAGEMANAGER->render("scoreFont", hdc, WINSIZEX + 20, 100);
	IMAGEMANAGER->render("spellFont", hdc, WINSIZEX + 20, 150);

	for (int i = 0; i < 12; i++)
	{
		if (_vScore.size() > i)
		{
			IMAGEMANAGER->frameRender("numbers", hdc, WINSIZEX + 130 + 13 * (12 - i), 107, _vScore[i], 0);
		}
		else {
			IMAGEMANAGER->frameRender("numbers", hdc, WINSIZEX + 130 + 13 * (12 - i), 107, 0, 0);
		}
	}

	IMAGEMANAGER->frameRender("numbers", hdc, WINSIZEX + 130 + 13, 57, _pPlayer->getPower() / 10, 0);
	IMAGEMANAGER->frameRender("numbers", hdc, WINSIZEX + 130 + 13 + 12, 57, _pPlayer->getPower() % 10, 0);

	IMAGEMANAGER->frameRender("numbers", hdc, WINSIZEX + 130 + 13, 157, _pPlayer->getSpellCount(), 0);

}

void C_UIMGR::createHpBar()
{
	_pHpBar = new C_BAR();
	_pHpBar->init();
}

void C_UIMGR::destoryHpBar()
{
	_pHpBar->release();
}

void C_UIMGR::createLbUI()
{
	_pLBBar = new C_BAR();
	_pLBBar->init();
	_pLBBar->setSingle(true);
	_pLBBar->setImg("LBHpBar");
	_pLBBar->returnStartPixel();
}

void C_UIMGR::destoryLbUI()
{
	_pLBBar->release();
}

void C_UIMGR::setDamageLb(int nDamage)
{
	_pLBBar->getDamage(nDamage);
}

void C_UIMGR::setNomalizeDamageLb(int nDamage)
{
	_pLBBar->setNomalizeDamage(nDamage);
}

void C_UIMGR::returnBar()
{
	_pLBBar->returnStartPixel();
}

void C_UIMGR::setDamage(int nDamage)
{
	_pHpBar->getDamage(nDamage);
}

void C_UIMGR::setNomalizeDamage(int nDamage)
{
	_pHpBar->setNomalizeDamage(nDamage);
}
