#pragma once
#include "stdafx.h"
#include "player.h"
#include "bullet.h"

#include <list>
#include <queue>



class C_PLAYER;
class C_ENEMYMGR;
class C_EFFECTMGR;
//class C_UIMGR;
class C_ITEMMGR;

class C_BULLETMGR
{

public:
	C_BULLETMGR();
	~C_BULLETMGR();

private:
	const C_BULLETMGR& operator=(const C_BULLETMGR&);
	C_BULLETMGR(const C_BULLETMGR&);

private:
	queue<C_BULLET*>	_queMemPoolBullet;
	list<C_BULLET*>		_listAliveBullet;

	int					_nPoolCount;
	C_PLAYER*			_pPlayer;
	C_ENEMYMGR*			_pEnemyMgr;
	C_EFFECTMGR*		_pEffectMgr;
	int					_nChargingCount;		//Â÷Â¡µÈ ÃÑ¾Ë¼ö
	C_ITEMMGR*			_pItemMgr;
	//C_UIMGR*			_pUiMgr;

public:
	void	init(int nPoolCount);
	void	update();
	void	release();
	void	render();

	void	setEnemyMgr(C_ENEMYMGR* pEnemyMgr) { _pEnemyMgr = pEnemyMgr; }
	void	setPlayer(C_PLAYER* pPlayer);
	inline	void	setEffectMgr(C_EFFECTMGR* pEffectMgr) { _pEffectMgr = pEffectMgr; }
	inline	void	setItemMgr(C_ITEMMGR* pItemMgr) { _pItemMgr = pItemMgr; }
	//inline	void	setUiMgr(C_UIMGR* pUiMgr) { _pUiMgr = pUiMgr; }


	bool	fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame,bool bIsPlayers,C_BULLET::E_BULLETTYPE eBullet);
	bool	fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image * pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool bIsPlayers, C_BULLET::E_BULLETTYPE eBullet, int nStopFrame);
	bool	fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image* pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool _bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType, float fRange);

	void	setFrameY(int nIndex);
	void	serFrameX(int nIndex);
	void	findNearEnemy();

	inline	int		getSize() { return (int)_queMemPoolBullet.size(); }
	inline	int		getListSize() { return (int)_listAliveBullet.size(); }
	
	bool	onPlayerCollsion(float fPosX, float fPosY, float fRadius);
	int		onEnemyCollsion(float fPosX, float fPosY, int nWidth, int nHeight);
	bool	getNotEnemyBullet();

	void	clearBullet();

	void	setDamage(int nDamage);

	void	goHurricane();

	void	setfSpeed(float fSpeed);
	void	setLimitedRadius(float fRadius);
	void	setBottomRadius(float fRadius);
	void	setCircleX(float fX);
	void	setCircleY(float fY);
private:
	void	setMemPool();

};
