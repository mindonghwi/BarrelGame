#include "stdafx.h"
#include "saveLoadTest.h"


void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) load();

}

void saveLoadTest::save()
{
	//파일 입출력은 다양한 방식이 있다
	//C - FILE* <-- 파일포인터 기능은 적은데 매우 빠름
	//C++ - ifstream, ofstream 기능은 많은데 좀 느림
	//WIN32 - CreateFile() api전용

	//셋다 써도 무관한데 FILE*는 초심자들에겐 좀 어려울 것임. 아마..정말..
	
	HANDLE file;
	DWORD write;

	char str[128] = "민노스는 오늘도 과연 강의를 하는가!";

	file = CreateFile("민노스와자식들.txt", GENERIC_WRITE,
		FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	//원래는 캐릭터 배열을 잡을 필요없이 문자열 크기만큼만 동적배열생성을
	//해주는 것이 더 좋다.
	char str[128];

	file = CreateFile("민노스와자식들.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	//               메세지 박스 텍스트 출력     메세지박스스타일
	MessageBox(_hWnd, str, "슈팅게임프로젝트 화이팅", MB_OK);


}

saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}
