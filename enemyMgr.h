#pragma once


#include "gameNode.h"
#include "smoke.h"
#include "fairy.h"
#include "boss.h"
#include "flora.h"
#include "lastBoss.h"


class C_PLAYER;
class I_ENEMY;
class C_BULLETMGR;
class C_EFFECTMGR;
class C_UIMGR;
class C_ITEMMGR;

class C_ENEMYMGR:public gameNode
{
private:
	//몬스터 타입을 이넘으로 가지고 있을 것이다.
	enum class E_ENEMYTYPE
	{
		E_NONE = 0,
		E_FLORA,
		E_SMOKE,
		E_FAIRY,
		E_BOSS,
		E_LASTBOSS,
		E_MAX
	};

public:
	C_ENEMYMGR();
	~C_ENEMYMGR();

private:
	vector<I_ENEMY*>				_vEnemy;		//에네미들이 담길 벡터
	vector<I_ENEMY*>::iterator		_vitorEnemy;	//에네미들이 담긴 벡터를 가리킬 이터

	int								_nFrameCount;	//몬스터들이 나오는 프레임 시간을 제어할 변수
	bool							_nBIsNextStage;	//다음 스테이지 갈수 있다.
	C_BULLETMGR*					_pBulletMgr;	//불릿매니저 상호참조
	C_PLAYER*						_pPlayer;
	C_EFFECTMGR*					_pEffectMgr;
	C_UIMGR*						_pUiMgr;
	C_ITEMMGR*						_pItemMgr;
	bool							_bISLastBoss;
	bool							_bISGameEnd;
public:
	//게임노드 오버라이딩
	virtual HRESULT init()	override;
	virtual void update()	override;
	virtual void render()	override;
	virtual void release()	override;

private:
	//몬스터 생성 함수
	void	createEnemy(E_ENEMYTYPE eEnemyType,float fPosX,float fPosY,float fAngle,float fSpeed);

	void	onEnemyCollision();

public:
	inline void setBulletMgr(C_BULLETMGR* pBulletMgr) { _pBulletMgr = pBulletMgr; }
	inline void setPlayer(C_PLAYER* pPlayer) { _pPlayer= pPlayer; }
	inline void setEffectMgr(C_EFFECTMGR* pEffectMgr) { _pEffectMgr = pEffectMgr; }
	inline void setUiMgr(C_UIMGR* pUiMgr) { _pUiMgr = pUiMgr; }
	inline void setItemMgr(C_ITEMMGR* pItemMgr) { _pItemMgr = pItemMgr; }


	inline float getEnemyPosX(int nIndex) { return _vEnemy[nIndex]->getPosX(); }
	inline float getEnemyPosY(int nIndex) { return _vEnemy[nIndex]->getPosY(); }
	inline int	getEnemySize() { return (int)_vEnemy.size(); }

	inline	bool	getGameEnd() { return _bISGameEnd; }

	
};


//에네미가 죽을때마다
//에네미가 다 죽으면 남아있던 총알들
//자식이 누구인지 알게 하는 방법을 알면 이펙트를 매니저에서 처리가능 불가능하면 각 적에서 처리해야한다.
//체력게이지는 보스만 가지고 있는다.