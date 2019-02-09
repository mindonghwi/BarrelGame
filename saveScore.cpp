#include "stdafx.h"
#include "saveScore.h"

C_SAVETEXT::C_SAVETEXT()
{
}

C_SAVETEXT::~C_SAVETEXT()
{
}

bool C_SAVETEXT::saveHighScore(long long lScore)
{
	HANDLE file;
	DWORD write;

	if (lScore > _lHighScore)
	{
		char str[128];
		_lHighScore = lScore;

		sprintf_s(str, "%lli", lScore);

		file = CreateFile("HighScore.txt", GENERIC_WRITE,
			FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, str, strlen(str), &write, NULL);

		CloseHandle(file);
		return true;
	}


	return false;
}

long long C_SAVETEXT::loadHighScore()
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile("HighScore.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);



	_lHighScore = atoll(str);
	return _lHighScore;
}
