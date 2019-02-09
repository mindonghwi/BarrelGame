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
	
	//이동 관련 변수들
	bool			_bIsStartVertex;	//가로이동 시작
	
	bool			_bIsStartStarOfDavid;//육망성 이동 시작
	int				_nMovingFrameCount;		//움직임 프레임 

	bool			_bIsStartUnlimited;		//8자 운동 시작
	float			_arCirclePosX[2];		//서클의 x좌표를 기억하기 위한 변수
	float			_fCirclePosY;			//서클의 y좌표를 기억하기 위한 변수
	int				_nCircleIndex;			//무슨 원을 중심으로 돌지 정하는 인덱스
	float			_fChangePlusMinus;		//+ - 치환
	C_BOSS::E_MOVING _eMoveStatus;			//이동 상태 저장
	bool			_arStartMoving[static_cast<const int>(C_BOSS::E_MOVING::E_MAX)];

	//사격용 변수들
	float			_fChargingRotate;		//차징하면서 원으로 불릿을 깔기위한 함수
	bool			_bIsStartCharging;		//차징 시작
	int				_nChargingCycle;		//차징시 생기는 원의 크기
	C_BOSS::E_FIRETYPE _eFireType;			//쏘는 타입
	bool			_arStartFire[static_cast<const int>(C_BOSS::E_FIRETYPE::E_MAX)];

	//사격 이동 통제 변수
	int				_nTurn;					//보스의 다음 턴을 정한다 랜덤으로
	//임시변수 공간들
	int				_nCountVertex;

	float			_fWaveAngle;
	float			_fTurnAngle;
	image*			_pImgCremora;				//크레모아 이미지
	float			_arCremoraPosX[6];		//크레모아 좌표
	float			_arCremoraPosY[6];		//크레모아 좌표
	float			_arSpiralAngle[4];		//4방위 앵글값
	int				_nCremoraIndex;			//크레모어	인덱스
	int				_arCremoraFrameX[6];	//크레모어 프레임 x

	float			_arCircleOfPosX[12];	//서클 포지션
	float			_arCircleOfPosY[12];	//서클 포지션

	//꽃관련
	float			_arFlowerPosX[9];		
	float			_arFlowerPosY[9];
	bool			_bIsShotFlower;


	//뱅뱅 관련
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
	
	//패턴별로 이동과 사격을 정리할까?
	void	charzingShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//일단 쏴두고 한번에 퍼지는 패턴
	void	cramoreShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//수류탄같은 던지고 터지면서 다수의 총알이 나가는 패턴
	void    speedShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//속도가 빨라지는 패턴
	void	shakeShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);		//일정 범위를 이동하면 방향이 전환되는 총알 패턴
	void	circleDoubleShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);//
	void	flowerShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);
	void	bangbangShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);
	void	hwaRoonShot(C_BULLETMGR* pBulletMgr, C_PLAYER* pPlayer);	//삼각 포지션 세방형 쏴서 삼각 포지션을 중심으로하는 점에서 그 거리에서 벗어나면 커지게

	//아니면 이동도 패턴화 시킬까
	void	appear();			//등장
	void	moveVertex();		//가로로 이동
	void	moveStarOfDavid();	//육망성 이동
	void	moveUnlimited();	//8자모양 이동
	

	void	createCremora(int& nIndex);		//크레모어 생성
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

