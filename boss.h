#pragma once

#include "enemy.h"

class C_BOSS:public I_ENEMY
{
private:
	enum{E_STAROFDAVIDTURNFRAME = 70};
	enum class E_MOVING {
		E_NONE = 0,
		E_APPEAR,
		E_VERTEX,
		E_STAROFDAVID,
		E_UNLIMITED,
		E_STAND,
		E_MAX
	};

	enum class E_FIRETYPE {
		E_NONE = 0,
		E_CHARGING,
		E_SHAKESHOT,
		E_CREMORA,
		E_CIRCLE,
		E_BAMGBAMG,
		E_MAX
	};
public:
	C_BOSS();
	~C_BOSS();

private:
	const C_BOSS& operator=(const C_BOSS&);
	C_BOSS(const C_BOSS&);

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
	
	//�̵� ���� ������
	bool			_bIsStartVertex;	//�����̵� ����
	
	bool			_bIsStartStarOfDavid;//������ �̵� ����
	int				_nMovingFrameCount;		//������ ������ 

	bool			_bIsStartUnlimited;		//8�� � ����
	float			_arCirclePosX[2];		//��Ŭ�� x��ǥ�� ����ϱ� ���� ����
	float			_fCirclePosY;			//��Ŭ�� y��ǥ�� ����ϱ� ���� ����
	int				_nCircleIndex;			//���� ���� �߽����� ���� ���ϴ� �ε���
	float			_fChangePlusMinus;		//+ - ġȯ
	C_BOSS::E_MOVING _eMoveStatus;			//�̵� ���� ����
	bool			_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_MAX)];

	//��ݿ� ������
	float			_fChargingRotate;		//��¡�ϸ鼭 ������ �Ҹ��� ������� �Լ�
	bool			_bIsStartCharging;		//��¡ ����
	int				_nChargingCycle;		//��¡�� ����� ���� ũ��
	C_BOSS::E_FIRETYPE _eFireType;			//��� Ÿ��
	bool			_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_MAX)];

	//��� �̵� ���� ����
	int				_nTurn;					//������ ���� ���� ���Ѵ� ��������
	//�ӽú��� ������
	int				_nCountVertex;

	float			_fWaveAngle;
	float			_fTurnAngle;
	image*			_pImgCremora;				//ũ����� �̹���
	float			_arCremoraPosX[6];		//ũ����� ��ǥ
	float			_arCremoraPosY[6];		//ũ����� ��ǥ
	float			_arSpiralAngle[4];		//4���� �ޱ۰�
	int				_nCremoraIndex;			//ũ�����	�ε���
	int				_arCremoraFrameX[6];	//ũ����� ������ x

	float			_arCircleOfPosX[12];	//��Ŭ ������
	float			_arCircleOfPosY[12];	//��Ŭ ������

	//�ɰ���
	float			_arFlowerPosX[9];		
	float			_arFlowerPosY[9];
	bool			_bIsShotFlower;


	//��� ����
	image*			_pImgEffect;
	float			_arEffectPosX[19];
	float			_arEffectPosY[19];
	int				_arEFCurrentX[19];
	float			_fBangPosX;
	float			_fBangPosY;
	int				_nEffectIndex;
	float			_fBangAngle;
	float			_fBangRadius;



	int				_nHp;
private:
	
	//���Ϻ��� �̵��� ����� �����ұ�?
	void	charzingShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//�ϴ� ���ΰ� �ѹ��� ������ ����
	void	cramoreShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//����ź���� ������ �����鼭 �ټ��� �Ѿ��� ������ ����
	void    speedShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//�ӵ��� �������� ����
	void	shakeShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//���� ������ �̵��ϸ� ������ ��ȯ�Ǵ� �Ѿ� ����
	void	circleDoubleShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);//
	void	flowerShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);
	void	bangbangShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);
	void	hwaRoonShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);	//�ﰢ ������ ������ ���� �ﰢ �������� �߽������ϴ� ������ �� �Ÿ����� ����� Ŀ����

	//�ƴϸ� �̵��� ����ȭ ��ų��
	void	appear();			//����
	void	moveVertex();		//���η� �̵�
	void	moveStarOfDavid();	//������ �̵�
	void	moveUnlimited();	//8�ڸ�� �̵�
	

	void	createCremora(int& nIndex);		//ũ����� ����
	void	initCremora();
	void	renderCremora(HDC hDc);
	void	releaseCremora();
	
	void	initCircle();
	
	void	initFlowerPos();


	void	createEffect();
	void	releaseEffect(int nIndex);
	void	updateEffect();
	void	renderEffect(HDC hdc);
	void	clearEffect();
};

