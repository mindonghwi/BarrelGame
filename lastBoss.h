#pragma once
#pragma once

#include "enemy.h"

class C_LASTBOSS :public I_ENEMY
{
private:
	enum E_LIMITEMOVE {
		E_VERTICAL = 100,
		E_HORIZENTAL = 190
	};


	enum class E_MOVING {
		E_APPEAR = 0,
		E_STAY,
		E_MOVE,
		E_MAX
	};

	enum class E_FIRETYPE {
		E_NONE = 0,
		E_HERRICANE,
		E_TWOFLOWER,
		E_LEAFSTORM,
		E_ARC,
		E_MAX
	};
public:
	C_LASTBOSS();
	~C_LASTBOSS();

private:
	const C_LASTBOSS& operator=(const C_LASTBOSS&);
	C_LASTBOSS(const C_LASTBOSS&);

private:

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
	virtual float	getPosX() override;
	virtual float	getPosY() override;
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
	bool			_bIsRemove;			//��������ϴ��� üũ���ִ� �Լ�
	int				_nBulletReload;		//reload
	bool			_bIsFire;			//�ѽ��

	float			_fMoveCircleCenterX;
	float			_fMoveCircleCenterY;
	float			_fMoveTurn;


	int				_nHp;
	int				_nItem;
	int				_nLife;				//�� ������� (5 - life) * hp

	C_LASTBOSS::E_FIRETYPE	_eFireType;
	C_LASTBOSS::E_MOVING	_eMoveStatus;
	float			_fHurricaneAngle;

	int				_nMovingFrameCount;
	int				_nAnimaitionFrameCount;

	image*			_pImgEffect;
	int				_nFireCount;

	float			_arFosSpiralPosX[8];
	float			_arFosSpiralPosY[8];
	float			_arFosAngle[8];
	bool			_bIsStartFlowor;

	int				_nSmallFrameCount;

	bool			_bIsBulletClear;

private:
	//����01
	void	fireHurricane(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer,float foffSetAngle);
	
	//����02
	void	fireTwoFlower(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer, float foffSetAngle);
	void	initSprialPos();
	void	updateSprialPos();
	
	//����03
	void	fireLeafStorm(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);

	//����04
	void	fireArc(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer,float fCirclePosX,float fCirclePosY);
	void	fireCircle(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer, float fCirclePosX, float fCirclePosY);
	void	fireVine(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer, float fCirclePosX, float fCirclePosY);

};
