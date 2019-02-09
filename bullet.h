#pragma once
#include "stdafx.h"
#include "gameNode.h"


class C_BULLET : public gameNode
{
public:
	//�̰� ���� ������ �˾ƾ� �Ѵ�!!!
	//�׷� �̳��� ����ؼ� ���� �Ҹ����� �˰�����

	//�� �ʿ��ϳĸ� �� ������ �̵��� �ٸ��� �����̴�.

	enum class E_BULLETTYPE
	{
		E_NONE = 0,
		E_STRIGHT,
		E_HOMING,
		E_WAVE,
		E_DELEYTURN,
		E_CHASINGSHOT,
		E_MOVEDELEYRANDOM,
		E_LAZER,
		E_SPELL,
		E_HERICAIN,
		E_SLIDER,
		E_LEAFSTORM,
		E_STRIGHTSLOW,
		E_TRUETRI,
		E_INVERSETRI,
		E_CIRCLE,
		E_MAX
	};

public:
	C_BULLET();
	~C_BULLET();

private:
	const C_BULLET& operator=(const C_BULLET&);
	C_BULLET(const C_BULLET&);

private:
	float			_fPosX;						//�߽� x��ǥ
	float			_fPosY;						//�߽� y��ǥ
	int				_nWidth;					//���α���
	int				_nHeight;					//���α���
	float			_fUnitVectorAngle;			//�������� ����
	float			_fRotateAngle;				//ȸ�� ����
	float			_fSpeed;					//�ӵ�
	image*			_pImg;						//�̹���
	int				_nCollisionWidth;			//�浹 ���α���
	int				_nCollisionHeight;			//�浹 ���α���
	int				_nCurrentFrame;				//�� ������
	int				_nMaxFrame;					//�� ������
	bool			_bIsPlayerBullet;			//�÷��̾��� ������ �ƴ���
	E_BULLETTYPE	_eBulletType;				//�� Ÿ��
	int				_nAttacking;				//���ݷ� ��ġ
	bool			_bIsRemove;					//������ �ϴ� �� �˷��ִ� ����


	float			_fWavePosX;					//���̺�� x
	float			_fWavePosY;					//���̺�� y

	float			_fNearEnemyX;
	float			_fNearEnemyY;

	int				_nCurrentFrameY;			//������ y
	float			_fDis;						//enemy�� ���� �Ÿ�
	float			_fRange;					//�Ѱ迵��
	float			_fStartX;					//���� x
	float			_fStartY;					//���� y
	int				_nStopFrame;				//�����ִ� �ð�
	int				_nKeepFlowerFrame;			//�ɸ���� �����ϴ� �ð�

	int				_nTurnPower;				//�Ŀ� ���� ��ȯ
	float			_fLimitedRadius;			//����� �Ѱ� ����
	float			_fBottomRaddius;			//�����

	float			_fSavePosX;
	float			_fSavePosY;

public:
	//���� ��� �������̵� �� �Լ���
	//init�� �����ε�
	virtual HRESULT init()		override;
	virtual void	release()	override;
	virtual void	update()	override;
	virtual void	render()	override;

	//�Ҹ��� ȭ�� ������ �������� üũ
	bool			checkOutBullet();
	//�Ҹ��� ��ġ�� �ʱⰪ���� ������ �Լ�
	void			deleteBullet();
	//�߻��ϴ� �Լ�
	void			fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image* pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame,bool _bIsPlayers,C_BULLET::E_BULLETTYPE eBulletType);
	void			fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image* pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool _bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType,int nStopFrame);
	void			fire(float fPosX, float fPosY, float fUnitAngle, float fRotateAngle, image* pImg, float fSpeed, int nCollisionWidth, int nCollisionHeight, int nMaxFrame, bool _bIsPlayers, C_BULLET::E_BULLETTYPE eBulletType, float fRange);


	inline	int		getDamage() { return _nAttacking; }
	void			findAngleEnemy(float fPosX,float fPosY);
	void			setFraneY(int nIndex);
	void			setFraneX(int nIndex);

	inline C_BULLET::E_BULLETTYPE	getBullType() { return _eBulletType; }
	inline	bool					getIsPlayer() { return _bIsPlayerBullet; }
	inline	void					setBulletSpeed(float fSpeed) { _fSpeed = fSpeed; }
	inline	float					getPosX() { return _fPosX; }
	inline	float					getPoSY() { return _fPosY; }
	inline	int						getRadius() { return _nCollisionWidth; }
	inline	void					setDamage(int nAttacking) { _nAttacking = nAttacking; }
	inline  void					setBullType(C_BULLET::E_BULLETTYPE eBull) { _eBulletType = eBull; }
	inline	void					setfSpeed(float fSpeed) { _fSpeed = fSpeed; }
	inline	void					setLimitedRadius(float fRadius) { _fLimitedRadius = fRadius; }
	inline	void					setBottomRadius(float fRadius) { _fBottomRaddius = fRadius; }

	inline	void					setCircleX(float fX) { _fSavePosX = fX; }
	inline	void					setCircleY(float fY) { _fSavePosY = fY; }
	inline	void					setRndAngle() { _fUnitVectorAngle = RND->getFromFloatTo(0.0f, PI2); }

private:
	//�����̴� �Լ�
	void			moveStraight();
	void			moveHoming();
	void			moveWave();
	void			moveDeleyTurn();
	void			chargingShot();
	void			moveDeleyRanDom();
	void			moveLazer();
	void			moveSpell();

	//��Ʈ ������
	void			moveHericain();
	void			moveNotTimeSlider();
	void			moveLeafStorm();
	void			moveSlow();
	void			moveTrueTri();
	void			moveInverseTri();
	void			moveCircle();

	//�����Ӱ��� ����ִ� �Լ�
	void			setFrame();

};

