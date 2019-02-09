#pragma once

#include "stdafx.h"
#include "enemy.h"


//플로라는 직선운동만 한다!!!!
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
	C_FLORA::E_ANI	_eAni;				//애니메이션 상태
	bool			_bIsRemove;			//사라져야하는지 체크해주는 함수
	int				_nBulletReload;		//reload
	bool			_bIsFire;			//총쏘기
	int				_nHp;				//생명력

	image*			_pEffectImage;
	int				_nEffectFrameX;

};