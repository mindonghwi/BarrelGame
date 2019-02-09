#pragma once

#include "stdafx.h"
#include "enemy.h"



class C_FAIRY : public I_ENEMY
{
private:
	enum class E_ANIMATION {
		E_IDLE = 0,
		E_LEFT,
		E_RIGHT,
		E_MAX
	};

	enum class E_FAIRYBULLETTYPE
	{
		E_NONE = 0,
		E_SPIRAL,		//2������ ���鼭 ���
		E_PANEL,		//�ڽ��� ���� 4���� ��ġ�� �ִ� �ű⼭ ���� ������� �Ѵ�.
		E_MAX
	};
	enum class E_FRAMEDIS {
		E_LOW = 0,
		E_HIGH,
		E_MAX
	};

public:
	C_FAIRY();
	~C_FAIRY();

private:
	C_FAIRY(const C_FAIRY&);
	const C_FAIRY& operator=(const C_FAIRY&);

public:
	virtual void create(float fPosX, float fPosY, float fAngle, float fSpeed)	override;
	virtual void update()														override;
	virtual void release()														override;
	virtual void render(HDC hDc)												override;
	virtual void fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)				override;
	virtual bool checkRemove()													override;
	virtual bool checkFireOk() override;
	virtual float	getPosX()													override;
	virtual float	getPosY()													override;
	virtual int		getRadius()													override;
	virtual	void	damage(int nDamage)											override;
	virtual int		getHp()														override;
	virtual int		getItem()													override;
	virtual bool	bulletClear() override;

private:
	float						_fPosX;					//�߽��� x ��ġ
	float						_fPosY;					//�߽��� y ��ġ
	float						_fAngle;				//�̵�����
	int							_nWidth;				//���α���
	int							_nHeight;				//���α���
	float						_fSpeed;				//�ӵ�
	image*						_pImg;					//�̹���
	int							_nCurrentFrameX;		//�� ������ x
	int							_nCurrentFrameY;		//��	 ������ y
	int							_nAniMationFrame;		//�ִϸ��̼� ���� ������
	bool						_bIsRemove;				//��������ϴ��� üũ���ִ� �Լ�
	float						_fMovingChanging;		//�������� ���� y��ǥ�� ��
	C_FAIRY::E_ANIMATION		_eAniStatus;			//�ִϸ��̼� ����
	int							_nDeathCount;			//������ ī��Ʈ

	//�Ѿ� �ǳ� ����
	float						_arSpiralBulletAngle[4];//�����̷� ����

	float						_arPanelPosX[4];		//�ǳ� ��ġ x
	float						_arPanelPosY[4];		//�ǳ� ��ġ y
	image*						_pPanelImg;				//�ǳ� �̹���
	int							_nPanelCurrentFrameX;	//�ĳ� x ������
	bool						_bIsPanelOn;			//�ǳ� ����Ҷ�
	float						_arPanelAngle[4];		//�ǳ��� ����

	int							_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX)];	//������ ���
	bool						_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX)];		//��� �ִ��� üũ

	int							_arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_MAX)];		//������ ������ ��� �ִ���


	int							_nHp;				//�����


private:
	void		setPanel();
	void		renderPanel(HDC hDc);
	void		movePanel();

	void		setSpiral();
	void		moveSpiral();


};
