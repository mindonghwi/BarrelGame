#pragma once

#include "stdafx.h"
#include "effect.h"
#include <queue>
#include <list>


class C_EFFECTMGR
{
private:
	const C_EFFECTMGR& operator=(const C_EFFECTMGR&);
	C_EFFECTMGR(const C_EFFECTMGR&);


public:
	C_EFFECTMGR();
	~C_EFFECTMGR();

private:
	queue<C_EFFECT*>	_queEffectMemPool;
	list<C_EFFECT*>		_listAliveEffect;


	int				_nMemPoolCount;
public:

	void init(int nMemPoolCount);
	void update();
	void release();
	void render();



	void createEffect(float fPosX, float fPosY, const char* strImageKey);

	C_EFFECT*	getLastEffect() { return _listAliveEffect.back(); }

};