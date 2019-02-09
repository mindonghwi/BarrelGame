#pragma once
#include "bulletMgr.h"

class I_ENEMY abstract
{
public:
	//���׹� ����
	virtual void create(float fPosX, float fPosY, float fAngle, float fSpeed)	abstract;
	//������Ʈ
	virtual void update()		abstract;
	//�޸� ����
	virtual void release()		abstract;
	//���� ���ɵ�ø� ����Ѵ� �̳��� ���ӳ�带 ������� �ʱ⿡ �𸥴�!!!
	virtual void render(HDC hDc)		abstract;
	//�Ѿ˹߻�
	virtual void fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)			abstract;

	//��������ϴ��� �˷��ִ� �Լ�
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