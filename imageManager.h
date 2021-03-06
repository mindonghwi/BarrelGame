#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map> //사실 안해도 되는데 선언해봄 ㅋ _ㅋ

class imageManager : public singletonBase<imageManager>
{
private:
	//map<string, image*> <-- 얘를          mapImageList라 부르겠다.
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;


public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height, BOOL alpha = FALSE);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, BOOL alpha = FALSE);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, BOOL alpha = FALSE);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alpha = FALSE);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alpha = FALSE);

	//이미지를 찾는 함수
	image* findImage(string strKey);

	//싱글톤화 되어있는 이미지 지워주는 함쓔
	BOOL deleteImage(string strKey);

	//싸그리..
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void alphaLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

};

