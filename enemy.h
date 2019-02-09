#pragma once
#include "bulletMgr.h"

class I_ENEMY abstract
{
public:
	//에네미 생성
	virtual void create(float fPosX, float fPosY, float fAngle, float fSpeed)	abstract;
	//업데이트
	virtual void update()		abstract;
	//메모리 해제
	virtual void release()		abstract;
	//랜더 갯맴디시를 줘야한다 이넘은 게임노드를 상속하지 않기에 모른다!!!
	virtual void render(HDC hDc)		abstract;
	//총알발사
	virtual void fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)			abstract;

	//사라져야하는지 알려주는 함수
	virtual bool checkRemove() abstract;

	virtual bool checkFireOk() abstract;
	
	virtual float	getPosX() abstract;
	virtual float	getPosY() abstract;
	virtual int		getRadius() abstract;
	virtual	void	damage(int nDamage) abstract;
	
	virtual int		getHp() abstract;

	virtual int		getItem() abstract;

	virtual bool	bulletClear() abstract;
};