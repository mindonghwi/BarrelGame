#pragma once
#include "stdafx.h"
#include "gameNode.h"


class C_BULLET : public gameNode
{
public:
	//이게 무슨 블릿인지 알아야 한다!!!
	//그럼 이넘을 사용해서 무슨 불릿인지 알게하자

	//왜 필요하냐면 각 블릿마다 이동이 다르기 때문이다.

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
	float			_fPosX;						//중심 x좌표
	float			_fPosY;						//중심 y좌표
	int				_nWidth;					//가로길이
	int				_nHeight;					//세로길이
	float			_fUnitVectorAngle;			//단위벡터 각도
	float			_fRotateAngle;				//회전 각도
	float			_fSpeed;					//속도
	image*			_pImg;						//이미지
	int				_nCollisionWidth;			//충돌 가로길이
	int				_nCollisionHeight;			//충돌 세로길이
	int				_nCurrentFrame;				//현 프레임
	int				_nMaxFrame;					//끝 프레임
	bool			_bIsPlayerBullet;			//플레이어의 블릿인지 아닌지
	E_BULLETTYPE	_eBulletType;				//블릿 타입
	int				_nAttacking;				//공격력 수치
	bool			_bIsRemove;					//지워야 하는 지 알려주는 변수


	float			_fWavePosX;					//웨이브용 x
	float			_fWavePosY;					//웨이브용 y

	float			_fNearEnemyX;
	float			_fNearEnemyY;

	int				_nCurrentFrameY;			//프레임 y
	float			_fDis;						//enemy와 나의 거리
	float			_fRange;					//한계영역
	float			_fStartX;					//시작 x
	float			_fStartY;					//시작 y
	int				_nStopFrame;				//멈춰있는 시간
	int				_nKeepFlowerFrame;			//꽃모양을 유지하는 시간

	int				_nTurnPower;				//파워 방향 전환
	float			_fLimitedRadius;			//원운동시 한계 범위
	float			_fBottomRaddius;			//원운동시

	float			_fSavePosX;
	float			_fSavePosY;

public:
	//게임 노드 오버라이딩 한 함수들
	//init은 오버로딩
	virtual HRESULT init()		override;
	virtual void	release()	override;
	virtual void	update()	override;
	virtual void	render()	override;

	//불릿이 화면 밖으로 나갔는지 체크
	bool			checkOutBullet();
	//불릿의 위치를 초기값으로 돌리는 함수
	void			deleteBullet();
	//발사하는 함수
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
	//움직이는 함수
	void			moveStraight();
	void			moveHoming();
	void			moveWave();
	void			moveDeleyTurn();
	void			chargingShot();
	void			moveDeleyRanDom();
	void			moveLazer();
	void			moveSpell();

	//라스트 보스용
	void			moveHericain();
	void			moveNotTimeSlider();
	void			moveLeafStorm();
	void			moveSlow();
	void			moveTrueTri();
	void			moveInverseTri();
	void			moveCircle();

	//프레임값을 잡아주는 함수
	void			setFrame();

};

