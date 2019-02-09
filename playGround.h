#pragma once
#include "gameNode.h"

#include "saveLoadTest.h"
#include "player.h"
#include "bulletMgr.h"
#include "enemyMgr.h"
#include "effectMgr.h"
#include "uimgr.h"
#include "itemMgr.h"
#include "saveScore.h"

class playGround : public gameNode
{
private:
	C_PLAYER*		_pPlayer;		//플레이어
	C_BULLETMGR*	_pBulletMgr;	//불릿매니저
	C_ENEMYMGR*		_pEnemyMgr;		//에네미 매니저
	C_EFFECTMGR*	_pEffectMgr;
	C_UIMGR*		_pUiMgr;
	C_ITEMMGR*		_pItemMgr;

	C_SAVETEXT*		_pSaveScore;

	long long		_nFinalScore;

	bool			_bIsPlaying;
	bool			_bIsEnd;
	bool			_bIsHighScore;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	playGround();
	~playGround();

private:
	void loadImage();
	void settingCrossReference();
};

