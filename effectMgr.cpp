#include "stdafx.h"
#include "effectMgr.h"

C_EFFECTMGR::C_EFFECTMGR():
	_nMemPoolCount(0)
{
}

C_EFFECTMGR::~C_EFFECTMGR()
{
}



void C_EFFECTMGR::init(int nMemPoolCount)
{
	_nMemPoolCount = nMemPoolCount;

	for (int i = 0; i < _nMemPoolCount; i++)
	{
		C_EFFECT* pEffect;
		pEffect = new C_EFFECT();
		pEffect->init(-2000.0f, -2000.0f);
		_queEffectMemPool.push(pEffect);
	}
}

void C_EFFECTMGR::update()
{
	list<C_EFFECT*>::iterator	itor = _listAliveEffect.begin();
	list<C_EFFECT*>::iterator	end = _listAliveEffect.end();

	for (;itor != end;)
	{
		C_EFFECT* pEffect = *itor;
		pEffect->update();

		if (pEffect->getIsRemove())
		{
			pEffect->destroy();
			_queEffectMemPool.push(pEffect);
			itor = _listAliveEffect.erase(itor);
		}
		else {
			itor++;
		}
	}

}

void C_EFFECTMGR::release()
{
	list<C_EFFECT*>::iterator	itor = _listAliveEffect.begin();
	list<C_EFFECT*>::iterator	end = _listAliveEffect.end();

	for (; itor != end;)
	{
		C_EFFECT* pEffect = *itor;
		pEffect->release();
		itor = _listAliveEffect.erase(itor);
		delete pEffect;
		pEffect = nullptr;
	}

	while (!_queEffectMemPool.empty())
	{
		C_EFFECT* pEffect = _queEffectMemPool.front();
		pEffect->release();
		_queEffectMemPool.pop();
		delete pEffect;
		pEffect = nullptr;
	}

}

void C_EFFECTMGR::render()
{
	list<C_EFFECT*>::iterator	itor = _listAliveEffect.begin();
	list<C_EFFECT*>::iterator	end = _listAliveEffect.end();

	for (; itor != end;	itor++)
	{
		C_EFFECT* pEffect = *itor;
		pEffect->render();
	}
}

void C_EFFECTMGR::createEffect(float fPosX, float fPosY, const char * strImageKey)
{
	if (_queEffectMemPool.empty())
	{
		return;
	}

	C_EFFECT* pEffect = _queEffectMemPool.front();
	pEffect->create(fPosX, fPosY, strImageKey);
	_queEffectMemPool.pop();
	_listAliveEffect.push_back(pEffect);
}
