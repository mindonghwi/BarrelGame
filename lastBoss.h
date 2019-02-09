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

	//에네미 생성
	virtual void create(float fPosX, float fPosY, float fAngle, float fSpeed)	override;
	//업데이트
	virtual void update()														override;
	//메모리 해제
	virtual void release()														override;
	//랜더 갯맴디시를 줘야한다 이넘은 게임노드를 상속하지 않기에 모른다!!!
	virtual void render(HDC hDc)												override;
	//총알발사
	virtual void fire(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer)				override;

	//사라져야하는지 알려주는 함수
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
	float			_fPosX;				//중심의 x 위치
	float			_fPosY;				//중심의 y 위치
	float			_fAngle;			//이동각도
	int				_nWidth;			//가로길이
	int				_nHeight;			//세로길이
	float			_fSpeed;			//속도
	image*			_pImg;				//이미지
	int				_nCurrentFrameX;	//현 프레임 x
	int				_nCurrentFrameY;	//현	 프레임 y
	int				_nAniMationFrame;	//애니메이션 갱신 프레임
	bool			_bIsRemove;			//사라져야하는지 체크해주는 함수
	int				_nBulletReload;		//reload
	bool			_bIsFire;			//총쏘기

	float			_fMoveCircleCenterX;
	float			_fMoveCircleCenterY;
	float			_fMoveTurn;


	int				_nHp;
	int				_nItem;
	int				_nLife;				//총 생명력은 (5 - life) * hp

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
	//패턴01
	void	fireHurricane(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer,float foffSetAngle);
	
	//패턴02
	void	fireTwoFlower(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer, float foffSetAngle);
	void	initSprialPos();
	void	updateSprialPos();
	
	//패턴03
	void	fireLeafStorm(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);

	//패턴04
	void	fireArc(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer,float fCirclePosX,float fCirclePosY);
	void	fireCircle(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer, float fCirclePosX, float fCirclePosY);
	void	fireVine(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer, float fCirclePosX, float fCirclePosY);

};
