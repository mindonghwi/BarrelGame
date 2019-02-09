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
	//���� Ÿ���� �̳����� ������ ���� ���̴�.
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
	vector<I_ENEMY*>				_vEnemy;		//���׹̵��� ��� ����
	vector<I_ENEMY*>::iterator		_vitorEnemy;	//���׹̵��� ��� ���͸� ����ų ����

	int								_nFrameCount;	//���͵��� ������ ������ �ð��� ������ ����
	bool							_nBIsNextStage;	//���� �������� ���� �ִ�.
	C_BULLETMGR*					_pBulletMgr;	//�Ҹ��Ŵ��� ��ȣ����
	C_PLAYER*						_pPlayer;
	C_EFFECTMGR*					_pEffectMgr;
	C_UIMGR*						_pUiMgr;
	C_ITEMMGR*						_pItemMgr;
	bool							_bISLastBoss;
	bool							_bISGameEnd;
public:
	//���ӳ�� �������̵�
	virtual HRESULT init()	override;
	virtual void update()	override;
	virtual void render()	override;
	virtual void release()	override;

private:
	//���� ���� �Լ�
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


//���׹̰� ����������
//���׹̰� �� ������ �����ִ� �Ѿ˵�
//�ڽ��� �������� �˰� �ϴ� ����� �˸� ����Ʈ�� �Ŵ������� ó������ �Ұ����ϸ� �� ������ ó���ؾ��Ѵ�.
//ü�°������� ������ ������ �ִ´�.