#pragma once

#include "stdafx.h"

class C_BAR;
class C_ENEMYMGR;
class C_PLAYER;


class C_UIMGR
{
private:
	const C_UIMGR& operator=(const C_UIMGR&);
	C_UIMGR(const C_UIMGR&);

public:
	C_UIMGR();
	~C_UIMGR();

private:
	C_BAR * _pHpBar;
	
	C_BAR*	_pLBBar;


	C_ENEMYMGR* _pEnemyMgr;
	C_PLAYER*	_pPlayer;

	vector<int> _vScore;

public:
	void init();
	void update();
	void release();
	void render(HDC hdc);
	void createHpBar();
	void destoryHpBar();

	void createLbUI();
	void destoryLbUI();
	void	setDamageLb(int nDamage);//에네미가 알아야 하는 것
	void	setNomalizeDamageLb(int nDamage);//플레이어가 알아야하는 것
	void	returnBar();

	void	setDamage(int nDamage);//에네미가 알아야 하는 것
	void	setNomalizeDamage(int nDamage);//플레이어가 알아야하는 것
	inline void setEnemyMgr(C_ENEMYMGR* pEnemyMgr){ _pEnemyMgr = pEnemyMgr;}
	inline void setPlayer(C_PLAYER* pPlayer) { _pPlayer = pPlayer; }

	const C_BAR* gethpBar() { return _pHpBar; }
	const C_BAR* getLBBar() { return _pLBBar; }
	

};
