#include "stdafx.h"
#include "playGround.h"




playGround::playGround():
	_pPlayer(nullptr)
{
}


playGround::~playGround()
{
}

void playGround::loadImage()
{
	IMAGEMANAGER->addImage("backGround", "image/backGround.bmp", 600, 800, true, RGB(255, 0, 255),0);
	IMAGEMANAGER->addFrameImage("redbullet", "image/redbullet.bmp", 12, 52,1,1, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addFrameImage("bullet360", "image/bullet360.bmp", 1080, 30, 36, 1, true, RGB(255, 0, 255), true);

	
	//245 99 7 3 
	IMAGEMANAGER->addFrameImage("flora", "image/flora.bmp", 245, 99, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smoke", "image/smoke.bmp", 480, 60, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fairy", "image/fairy.bmp", 441, 165, 7, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SBullet", "image/songpeon.bmp", 540, 30, 36, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("magicPanel", "image/magicPanel.bmp", 400, 50, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("colorBullet", "image/colorBullet.bmp", 540, 120, 18, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss", "image/boss.bmp", 184, 300, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("circleBullet", "image/circleBullet.bmp", 196, 28, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cremora", "image/cremora.bmp", 240, 30, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("arrow", "image/arrow.bmp", 1080, 29, 35, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("flowerBullet", "image/flowerBullet.bmp", 224, 28, 8, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("effect", "image/effect.bmp", 950, 50, 19, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("circleSmallBullet", "image/circleSmallBullet.bmp", 70, 10, 7, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("enemyEffectDeath", "image/enemyEffectDeath.bmp", 840, 120, 7, 1, true, Mins::getMazenta(),true);
	IMAGEMANAGER->addFrameImage("effectRainBow", "image/effectRainBow.bmp", 2600, 100, 26, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("bulletDeleteEffect", "image/bulletDeleteEffect.bmp", 384, 47, 8, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("hpBarBack", "image/hpBarBackSmall.bmp", 500, 30, true, Mins::getMazenta(), true);
	IMAGEMANAGER->addImage("HpBarFront", "image/HpBarFrontSmall.bmp", 500, 30, true, Mins::getMazenta(), true);
	IMAGEMANAGER->addImage("power", "image/item/Power.bmp", 12, 12, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("score", "image/item/Score.bmp", 12, 12, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("bomb", "image/item/bomb.bmp", 16, 16, true, Mins::getMazenta());
	IMAGEMANAGER->addFrameImage("spell", "image/spell.bmp", 62, 62, 1, 1, true, Mins::getMazenta());


	IMAGEMANAGER->addFrameImage("num1000", "image/side/num1000.bmp", 101, 33, 1, 1, true, Mins::getMazenta(),true);
	IMAGEMANAGER->addFrameImage("num2000", "image/side/num2000.bmp", 111, 33, 1, 1, true, Mins::getMazenta(),true);
	IMAGEMANAGER->addFrameImage("num6000", "image/side/num6000.bmp", 113, 33, 1, 1, true, Mins::getMazenta(),true);
	IMAGEMANAGER->addFrameImage("num8000", "image/side/num8000.bmp", 111, 33, 1, 1, true, Mins::getMazenta(),true);

	IMAGEMANAGER->addImage("sidebackground", "image/side/sideBackGround.bmp", 300, 800, false, Mins::getMazenta());

	IMAGEMANAGER->addImage("scoreFont", "image/side/score.bmp", 120, 33, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("powerFont", "image/side/power.bmp", 120, 29, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("spellFont", "image/side/spellFont.bmp", 120, 44, true, Mins::getMazenta());

	IMAGEMANAGER->addImage("name", "image/side/name.bmp", 200, 389, true, Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("numbers", "image/side/number.bmp", 130, 14, 10, 1,true,Mins::getMazenta());

	IMAGEMANAGER->addFrameImage("lastBoss", "image/lastBoss.bmp", 280, 70, 4, 1, true, Mins::getMazenta());
	IMAGEMANAGER->addImage("lbEffect", "image/LBEffect.bmp", 245, 240, true, Mins::getMazenta());

	IMAGEMANAGER->addImage("endScreen", "image/endScreen.bmp", 900, 800, false, Mins::getMazenta());
	IMAGEMANAGER->addImage("startScreen", "image/startScreen.bmp", 900, 800, false, Mins::getMazenta());

	IMAGEMANAGER->addImage("LBHpBar", "image/LBHpBar.bmp", 600, 10, true, Mins::getMazenta(),true);

	IMAGEMANAGER->addFrameImage("bingNumber", "image/side/num.bmp", 330, 33, 10, 1, true, Mins::getMazenta());

	IMAGEMANAGER->addImage("highScore","image/side/HighScore.bmp",500, 500,true,Mins::getMazenta());
	IMAGEMANAGER->addImage("newHighScore", "image/side/newHighScore.bmp", 500, 500, true, Mins::getMazenta());
}

void playGround::settingCrossReference()
{
	_pBulletMgr->setPlayer(_pPlayer);
	_pBulletMgr->setEnemyMgr(_pEnemyMgr);

	_pPlayer->setBulletMgr(_pBulletMgr);
	_pPlayer->setEnemyMgr(_pEnemyMgr);

	_pEnemyMgr->setBulletMgr(_pBulletMgr);
	_pEnemyMgr->setPlayer(_pPlayer);

	_pBulletMgr->setEffectMgr(_pEffectMgr);
	_pPlayer->setEffectMgr(_pEffectMgr);
	_pEnemyMgr->setEffectMgr(_pEffectMgr);

	_pPlayer->setUiMgr(_pUiMgr);
	_pEnemyMgr->setUiMgr(_pUiMgr);
	
	_pItemMgr->setBulletMgr(_pBulletMgr);
	_pItemMgr->setEffectMgr(_pEffectMgr);
	_pItemMgr->setEnemyMgr(_pEnemyMgr);
	_pItemMgr->setPlayerMgr(_pPlayer);

	_pEnemyMgr->setItemMgr(_pItemMgr);
	_pBulletMgr->setItemMgr(_pItemMgr);

	_pUiMgr->setPlayer(_pPlayer);

}


HRESULT playGround::init()
{
	gameNode::init(true);
	loadImage();
	
	_pPlayer = new C_PLAYER();
	_pPlayer->init();
	
	_pBulletMgr = new C_BULLETMGR();
	_pBulletMgr->init(8000);

	_pEnemyMgr = new C_ENEMYMGR();
	_pEnemyMgr->init();

	_pEffectMgr = new C_EFFECTMGR();
	_pEffectMgr->init(8000);

	_pUiMgr = new C_UIMGR();
	_pUiMgr->init();

	_pItemMgr = new C_ITEMMGR();
	_pItemMgr->init(8000);

	settingCrossReference();

	_bIsPlaying = false;
	_bIsEnd = true;


	_pSaveScore = new C_SAVETEXT();
	_bIsHighScore = false;

	return S_OK;
}


void playGround::release()
{

	gameNode::release();

	delete _pSaveScore;
	_pSaveScore = nullptr;

	SAFE_RELEASE(_pPlayer);
	SAFE_RELEASE(_pEnemyMgr);
	SAFE_RELEASE(_pUiMgr);
	SAFE_RELEASE(_pItemMgr);
	SAFE_RELEASE(_pEffectMgr);
	SAFE_RELEASE(_pBulletMgr);

	SAFE_DELETE(_pBulletMgr);
	SAFE_DELETE(_pPlayer);
	SAFE_DELETE(_pEnemyMgr);
	SAFE_DELETE(_pUiMgr);
	SAFE_DELETE(_pItemMgr);
	SAFE_DELETE(_pEffectMgr);

}


void playGround::update()
{
	gameNode::update();

	if (!_bIsPlaying && _bIsEnd)
	{
		//시작 대기 상황
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_bIsPlaying = true;
			_bIsEnd = false;
		}
	}

	else if (_bIsPlaying && !_bIsEnd)
	{
		//게임중
		_pPlayer->update();

		_pBulletMgr->update();
		_pEnemyMgr->update();
		_pEffectMgr->update();


		_pUiMgr->update();
		_pItemMgr->update();


		if (_pEnemyMgr->getGameEnd())
		{
			_bIsEnd = true;
			_nFinalScore = _pPlayer->getScore();
			_pSaveScore->loadHighScore();

			if (_pSaveScore->saveHighScore(_nFinalScore))
			{
				_bIsHighScore = true;
			}
			else {
				_nFinalScore = _pSaveScore->getHighScore();
			}
		}
	}

	else if (_bIsPlaying && _bIsEnd)
	{
		//종료 상황
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_bIsPlaying = false;
			_bIsEnd = true;
			this->init();

		}
	}
	
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX + 300, WINSIZEY, WHITENESS);


	if (_bIsPlaying && !_bIsEnd) {
		IMAGEMANAGER->render("backGround", getMemDC());

		_pEffectMgr->render();
		_pEnemyMgr->render();
		_pItemMgr->render(getMemDC());

		_pPlayer->render();
		_pBulletMgr->render();


		IMAGEMANAGER->render("sidebackground", getMemDC(), WINSIZEX, 0);
		IMAGEMANAGER->render("name", getMemDC(), WINSIZEX + 100, 800 - 389);
		_pUiMgr->render(getMemDC());

	}
	if (!_bIsPlaying && _bIsEnd)
	{
		IMAGEMANAGER->render("startScreen", getMemDC());
	}
	if (_bIsPlaying && _bIsEnd) {
		IMAGEMANAGER->render("endScreen", getMemDC());

		if (_bIsHighScore)
		{
			IMAGEMANAGER->render("newHighScore", getMemDC(), 150, 100);
		}
		else
		{
			IMAGEMANAGER->render("highScore", getMemDC(), 150, 100);
		}
		long long llScore = _nFinalScore;
		for (int i = 0; i < 12; i++)
		{
			int	nNum = llScore % 10;
			IMAGEMANAGER->frameRender("bingNumber", getMemDC(), 786 - i * 33, WINSIZEY/2,nNum,0);
			llScore /= 10;
		}
	}



	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

