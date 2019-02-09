#pragma once


#include "gameNode.h"
#include "bulletMgr.h"



class C_BULLETMGR;
class C_ENEMYMGR;
class C_EFFECTMGR;
class C_UIMGR;
class C_ITEMMGR;

class C_PLAYER : public gameNode
{
private:
	enum E_PLAYERSTATE
	{
		E_IDLE = 0,
		E_LEFTMOVE,
		E_RIGHTMOVE,
		E_MAX
	};

public:
	C_PLAYER();									//기본생성자
	~C_PLAYER();								//기본소멸자

private:
	C_PLAYER(const C_PLAYER& );					//복사생성자 제거
	C_PLAYER& operator=(const C_PLAYER &);		//대입연산자 제거


private:
	float			_fPosX;						//플레이어 중앙값 x
	float			_fPosY;						//플레이어 중앙값 y
	int				_nWidth;					//플레이어 가로길이
	int				_nHeight;					//플레이어 세로길이
	float			_fAngle;					//플레이어 이동 각도
	int				_nCollisionRadius;			//플레이어 충돌 원 반지름
	image*			_pImg;						//플레이어 이미지
	float			_fSpeed;					//플레이어 스피드
												
	int				_nFrameCount;				//플레이어 프레임 카운트
	E_PLAYERSTATE	_ePlayerState;				//플레이어 상태 체크
	int				_nFrameX;					//플레이어 프레임 x번째 값
	C_BULLETMGR*	_pBulletMgr;				//불릿 매니저
	
	int				_nPower;					//플레이어 파위
	long long		_nScore;					//플레이어 스코어
	int				_nSpellCount;				//스펠 수

	int				_nBulletFrameCount;			//총알 리로드 텀
	int				_arPowerNPosX[3];			//파워당 직선총알 발사 x위치를 저장

	C_ENEMYMGR*		_pEnemyMgr;
	C_EFFECTMGR*	_pEffectMgr;
	BYTE			_Color[3];


	C_UIMGR*		_pUiMgr;
	vector<int>		_vScore;

public:
	//게임 노드 오버라이딩 한 함수들
	virtual HRESULT init()		override;
	virtual void	release()	override;
	virtual void	update()	override;
	virtual void	render()	override;


private:
	//플레이어 애니메이션 작용 함수
	void			playAnimation();
	void			powerUp();

public:
	float	getPosX() { return _fPosX; }
	float	getPosY() { return _fPosY; }
	void	setBulletMgr(C_BULLETMGR * pBulletMgr);
	void	setEnemyMgr(C_ENEMYMGR* pEnemyMgr) { _pEnemyMgr = pEnemyMgr; }
	void	setEffectMgr(C_EFFECTMGR* pEffectMgr) { _pEffectMgr = pEffectMgr; }

	inline	void	setUiMgr(C_UIMGR* pUiMgr) { _pUiMgr = pUiMgr; }


	inline	int		getWidth() { return _nWidth; }
	inline	int		getHeight() { return _nHeight; }
	inline	int		getPower() { return _nPower; }
	inline	int		getSpellCount() { return _nSpellCount; }
	vector<int>		getScores();
	inline	long long	getScore() { return _nScore; }

	inline	void	addSpell(int nPoint) { _nSpellCount+= nPoint; }
	inline	void	addScore(int nPoint) { _nScore += nPoint; }
	void	addPower(int nPoint);

private:
	void	onCollision();

	void	useSpell();
	void	updateSpell();
	void	initSpell();


private:
	image * pImage;
	int nRadius;
	bool	_bIsSpell;
};
