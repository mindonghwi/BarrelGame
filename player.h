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
	C_PLAYER();									//�⺻������
	~C_PLAYER();								//�⺻�Ҹ���

private:
	C_PLAYER(const C_PLAYER& );					//��������� ����
	C_PLAYER& operator=(const C_PLAYER &);		//���Կ����� ����


private:
	float			_fPosX;						//�÷��̾� �߾Ӱ� x
	float			_fPosY;						//�÷��̾� �߾Ӱ� y
	int				_nWidth;					//�÷��̾� ���α���
	int				_nHeight;					//�÷��̾� ���α���
	float			_fAngle;					//�÷��̾� �̵� ����
	int				_nCollisionRadius;			//�÷��̾� �浹 �� ������
	image*			_pImg;						//�÷��̾� �̹���
	float			_fSpeed;					//�÷��̾� ���ǵ�
												
	int				_nFrameCount;				//�÷��̾� ������ ī��Ʈ
	E_PLAYERSTATE	_ePlayerState;				//�÷��̾� ���� üũ
	int				_nFrameX;					//�÷��̾� ������ x��° ��
	C_BULLETMGR*	_pBulletMgr;				//�Ҹ� �Ŵ���
	
	int				_nPower;					//�÷��̾� ����
	long long		_nScore;					//�÷��̾� ���ھ�
	int				_nSpellCount;				//���� ��

	int				_nBulletFrameCount;			//�Ѿ� ���ε� ��
	int				_arPowerNPosX[3];			//�Ŀ��� �����Ѿ� �߻� x��ġ�� ����

	C_ENEMYMGR*		_pEnemyMgr;
	C_EFFECTMGR*	_pEffectMgr;
	BYTE			_Color[3];


	C_UIMGR*		_pUiMgr;
	vector<int>		_vScore;

public:
	//���� ��� �������̵� �� �Լ���
	virtual HRESULT init()		override;
	virtual void	release()	override;
	virtual void	update()	override;
	virtual void	render()	override;


private:
	//�÷��̾� �ִϸ��̼� �ۿ� �Լ�
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
