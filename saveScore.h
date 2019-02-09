#pragma once


#include "stdafx.h"


class C_SAVETEXT {
private:
	C_SAVETEXT(const C_SAVETEXT&);
	const C_SAVETEXT& operator=(const C_SAVETEXT&);

public:
	C_SAVETEXT();
	~C_SAVETEXT();


	bool saveHighScore(long long lScore);
	long long loadHighScore();

	inline long long getHighScore() { return _lHighScore; }

private:
	long long _lHighScore;


};