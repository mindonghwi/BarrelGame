#pragma once
#include "stdafx.h"
#include "gameNode.h"


class C_BAR: public gameNode
{
private:
	const C_BAR& operator=(const C_BAR&);
	C_BAR(const C_BAR&);

public:
	C_BAR();
	~C_BAR();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


private:
	float	_fLeft;
	float	_fTop;
	string	_strBack;
	string	_strFront;
	float	_fLastPixel;//102
	BYTE	_byteAlpha;
	float	_fStartPoxel;
	float	_fNomalizeDamage;
	bool	_bIsDraw;
	bool	_bISSingle;

public:
	inline	void	getDamage(int nDamage) { _fStartPoxel = _fStartPoxel - (_fNomalizeDamage * (float)nDamage); }
	inline	void	setSingle(bool bIsSingle) { _bISSingle = bIsSingle; }
	void	setImg(string strFront);
	void	setNomalizeDamage(int nHp);
	inline	void	returnStartPixel() { _fStartPoxel = 500; }
};
