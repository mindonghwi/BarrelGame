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
	virtual float	getPosX()													override;
	virtual float	getPosY()													override;
	virtual int		getRadius()													override;
	virtual	void	damage(int nDamage)											override;
	virtual int		getHp()														override;
	virtual int		getItem()													override;
	virtual bool	bulletClear() override;

private:
	float					_fPosX;				//중심의 x 위치
	float					_fPosY;				//중심의 y 위치
	float					_fAngle;			//이동각도
	int						_nWidth;			//가로길이
	int						_nHeight;			//세로길이
	float					_fSpeed;			//속도
	image*					_pImg;				//이미지
	int						_nCurrentFrameX;	//현 프레임 x
	int						_nAniMationFrame;	//애니메이션 갱신 프레임
	bool					_bIsRemove;			//사라져야하는지 체크해주는 함수
	C_SMOKE::E_MOVEPHASE	_eMovePhase;		//움직임 처리
	float					_fCircleCenterX;	//원운동시 원의 중점 x
	float					_fCircleCenterY;	//원운동시 원의 중점 y
	int						_nAniFrameCount;	//애니메이션 처리한 프레임 카운트
	int						_nCircleCycleCount;	//회전한 수

	int						_nFireReloadCount;	//총알 리로드 카운터
	bool					_bIsFire;			//

	int						_nHp;				//생명력

public:
};