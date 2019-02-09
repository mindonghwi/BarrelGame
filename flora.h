#pragma once

#include "stdafx.h"
#include "enemy.h"


//�÷ζ�� ������� �Ѵ�!!!!
class C_FLORA : public I_ENEMY {
private:
	enum E_ANI
	{
		E_IDLE = 0,
		E_LEFT,
		E_RIGHT,
		E_MAX
	};


public:
	C_FLORA();
	~C_FLORA();
private:
	C_FLORA(const C_FLORA&);
	const C_FLORA& operator=(const C_FLORA&);

public:
	virtual void create(float fPosX,float fPosY,float fAngle, float fSpeed)		override;
	virtual void update()														override;
	virtual void release()														override;
	virtual void render(HDC hDc)												override;
	virtual void fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)				override;
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
	float			_fPosX;				//�߽��� x ��ġ
	float			_fPosY;				//�߽��� y ��ġ
	float			_fAngle;			//�̵�����
	int				_nWidth;			//���α���
	int				_nHeight;			//���α���
	float			_fSpeed;			//�ӵ�
	image*			_pImg;				//�̹���
	int				_nCurrentFrameX;	//�� ������ x
	int				_nCurrentFrameY;	//��	 ������ y
	int				_nAniMationFrame;	//�ִϸ��̼� ���� ������
	C_FLORA::E_ANI	_eAni;				//�ִϸ��̼� ����
	bool			_bIsRemove;			//��������ϴ��� üũ���ִ� �Լ�
	int				_nBulletReload;		//reload
	bool			_bIsFire;			//�ѽ��
	int				_nHp;				//�����

	image*			_pEffectImage;
	int				_nEffectFrameX;

};