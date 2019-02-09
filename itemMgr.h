#pragma once
#include "stdafx.h"
#include "item.h"
#include <list>
#include <queue>
#include <vector>

class C_BULLETMGR;
class C_PLAYER;
class C_ENEMYMGR;
class C_UIMGR;
class C_EFFECTMGR;

class C_ITEMMGR
{
private:
	const C_ITEMMGR& operator= (const C_ITEMMGR&);
	C_ITEMMGR(const C_ITEMMGR&);

public:
	C_ITEMMGR();
	~C_ITEMMGR();

private:
	list<I_ITEM*>			_listItemAlive;
	//임시
	vector<queue<I_ITEM*>*>	_vqItemPool;			//아이템 개수만큼

	

	C_BULLETMGR *	_pBulletMgr;
	C_ENEMYMGR*		_pEnemyMgr;
	C_UIMGR*		_pUiMgr;
	C_EFFECTMGR*	_pEffectMgr;
	C_PLAYER*		_pPlayer;

	int				_nMemPoolCount;
	bool			_bISDrain;

public:
	void	init(int nMaxCount);
	void	update();
	void	release();
	void	render(HDC hdc);

	void	createItem(float fPosX, float fPosY, I_ITEM::E_ITEMTYPE eItem);
	bool	onCollision(float fPosX, float fPosY, int nWidth, int nHeight,I_ITEM* pITem);


	inline void	setBulletMgr(C_BULLETMGR * pBulletMgr) { _pBulletMgr = pBulletMgr; }
	inline void	setEnemyMgr	(C_ENEMYMGR* pEnemyMgr) { _pEnemyMgr = pEnemyMgr; }
	inline void	setEffectMgr(C_EFFECTMGR* pEffectMgr) { _pEffectMgr = pEffectMgr; }
	inline void	setPlayerMgr(C_PLAYER* pPlayer) { _pPlayer = pPlayer; }

	int	getListCount() { return (int)_listItemAlive.size(); }
};
