#pragma once
#include "stdafx.h"
#include "gameNode.h"

class C_EFFECT :public gameNode{
public:

private:
	const C_EFFECT& operator= (const C_EFFECT&);
	C_EFFECT(const C_EFFECT&);

public:
	C_EFFECT();
	~C_EFFECT();

private:
	float		_fPosX;
	float		_fPosY;
	string		_strImageKey;
	image*		_pImg;
	int			_nCurrentFrameX;
	int			_nMaxFrame;
	bool		_bIsRemove;
	int			_nFrameCount;
	BYTE		_byteAlphaRander;
	int			_nWidth;
	int			_nHeight;


public:
	void	init(float fPosX,float fPosY);
	virtual void release();
	virtual void update();
	virtual void render();
	void	create(float fPosX, float fPosY, const char* str);
	inline	bool	getIsRemove() { return _bIsRemove; }
	void	destroy();

};