#include "stdafx.h"
#include "saveLoadTest.h"


void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) load();

}

void saveLoadTest::save()
{
	//���� ������� �پ��� ����� �ִ�
	//C - FILE* <-- ���������� ����� ������ �ſ� ����
	//C++ - ifstream, ofstream ����� ������ �� ����
	//WIN32 - CreateFile() api����

	//�´� �ᵵ �����ѵ� FILE*�� �ʽ��ڵ鿡�� �� ����� ����. �Ƹ�..����..
	
	HANDLE file;
	DWORD write;

	char str[128] = "�γ뽺�� ���õ� ���� ���Ǹ� �ϴ°�!";

	file = CreateFile("�γ뽺���ڽĵ�.txt", GENERIC_WRITE,
		FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	//������ ĳ���� �迭�� ���� �ʿ���� ���ڿ� ũ�⸸ŭ�� �����迭������
	//���ִ� ���� �� ����.
	char str[128];

	file = CreateFile("�γ뽺���ڽĵ�.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	//               �޼��� �ڽ� �ؽ�Ʈ ���     �޼����ڽ���Ÿ��
	MessageBox(_hWnd, str, "���ð���������Ʈ ȭ����", MB_OK);


}

saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}
