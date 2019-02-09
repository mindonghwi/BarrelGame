#pragma once
#include "stdafx.h"
#include "enemy.h"


class C_SMOKE : public I_ENEMY
{
private:
	enum class E_MOVEPHASE
	{
		E_NONE = 0,
		E_STRIGHT,
		E_LEFTMOVECIRCLE,
		E_RIGHTMOVECIRCLE,
		E_MAX
	};

	enum{E_RELOADTIME = 300};
public:
	C_SMOKE();
	~C_SMOKE();

private:
	const C_SMOKE& operator= (const C_SMOKE&);
	C_SMOKE(const C_SMOKE&);

public:
	//���׹� ����
	virtual void create(float fPosX, float fPosY, float fAngle, float fSpeed)	override;
	//������Ʈ
	virtual void update()														override;
	//�޸� ����
	virtual void release()														override;
	//���� ���ɵ�ø� ����Ѵ� �̳��� ���ӳ�带 ������� �ʱ⿡ �𸥴�!!!
	virtual void render(HDC hDc)												override;
	//�Ѿ˹߻�
	virtual void fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)				override;

	//��������ϴ��� �˷��ִ� �Լ�
	virtual bool checkRemove()													override;
	virtual bool checkFireOk()													override;
	virtual float	getPosX()													override;
	virtual float	getPosY()													override;
	virtual int		getRadius()													override;
	virtual	void	damage(int nDamage)											override;
	virtual int		getHp()														override;
	virtual int		getItem()													override;
	virtual bool	bulletClear() override;

private:
	float					_fPosX;				//�߽��� x ��ġ
	float					_fPosY;				//�߽��� y ��ġ
	float					_fAngle;			//�̵�����
	int						_nWidth;			//���α���
	int						_nHeight;			//���α���
	float					_fSpeed;			//�ӵ�
	image*					_pImg;				//�̹���
	int						_nCurrentFrameX;	//�� ������ x
	int						_nAniMationFrame;	//�ִϸ��̼� ���� ������
	bool					_bIsRemove;			//��������ϴ��� üũ���ִ� �Լ�
	C_SMOKE::E_MOVEPHASE	_eMovePhase;		//������ ó��
	float					_fCircleCenterX;	//����� ���� ���� x
	float					_fCircleCenterY;	//����� ���� ���� y
	int						_nAniFrameCount;	//�ִϸ��̼� ó���� ������ ī��Ʈ
	int						_nCircleCycleCount;	//ȸ���� ��

	int						_nFireReloadCount;	//�Ѿ� ���ε� ī����
	bool					_bIsFire;			//

	int						_nHp;				//�����

public:
};