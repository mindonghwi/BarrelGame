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
		E_SPIRAL,		//2바퀴를 돌면서 사격
		E_PANEL,		//자신을 도는 4개의 위치가 있다 거기서 직선 사방위을 한다.
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
	float						_fPosX;					//중심의 x 위치
	float						_fPosY;					//중심의 y 위치
	float						_fAngle;				//이동각도
	int							_nWidth;				//가로길이
	int							_nHeight;				//세로길이
	float						_fSpeed;				//속도
	image*						_pImg;					//이미지
	int							_nCurrentFrameX;		//현 프레임 x
	int							_nCurrentFrameY;		//현	 프레임 y
	int							_nAniMationFrame;		//애니메이션 갱신 프레임
	bool						_bIsRemove;				//사라져야하는지 체크해주는 함수
	float						_fMovingChanging;		//움직임이 멈출 y좌표축 값
	C_FAIRY::E_ANIMATION		_eAniStatus;			//애니메이션 상태
	int							_nDeathCount;			//죽음의 카운트

	//총알 판넬 관련
	float						_arSpiralBulletAngle[4];//스파이럴 각도

	float						_arPanelPosX[4];		//판넬 위치 x
	float						_arPanelPosY[4];		//판넬 위치 y
	image*						_pPanelImg;				//판넬 이미지
	int							_nPanelCurrentFrameX;	//파넬 x 프레임
	bool						_bIsPanelOn;			//판넬 써야할때
	float						_arPanelAngle[4];		//판넬의 각도

	int							_arFireTimer[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX)];	//프레임 계산
	bool						_arIsFiring[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX)];		//쏠수 있는지 체크

	int							_arFireTime[static_cast<const int>(C_FAIRY::E_FAIRYBULLETTYPE::E_MAX)][static_cast<const int>(C_FAIRY::E_FRAMEDIS::E_MAX)];		//어디부터 어디까지 쏠수 있는지


	int							_nHp;				//생명력


private:
	void		setPanel();
	void		renderPanel(HDC hDc);
	void		movePanel();

	void		setSpiral();
	void		moveSpiral();


};
