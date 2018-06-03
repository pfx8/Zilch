//*****************************************************************************
//
// �G���W���R�A�t�@�C�� [Engine.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine.h"

//*****************************************************************************
//
// string to wstring
//
//*****************************************************************************
wstring stringToWstring(const string s)
{
	// wchar_t������̒������擾
	int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);

	// wchar_t������o�b�t�@��ݒ�
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));

	// �R�[�h�ύX
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	
	// wchar_t�������wstring�ɓ����
	wstring wstr;
	wstr = (wchar_t*)pUnicode;

	// �Վ��|�C���^�������[�X
	delete pUnicode;

	return wstr;
}

//*****************************************************************************
//
// wstring to string
//
//*****************************************************************************
string wstringToString(const wstring ws)
{
	// wchar_t������̒������擾
	int utfLen = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);

	// char_t������o�b�t�@��ݒ�
	char* elementText;
	elementText = new char[utfLen + 1];
	memset((void*)elementText, 0, sizeof(char)*(utfLen + 1));

	// �R�[�h�ύX
	WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, elementText, utfLen, NULL, NULL);

	// char�������string�ɓ����
	string str;
	str = elementText;

	// �Վ��|�C���^�������[�X
	delete[] elementText;

	return str;
}

//*****************************************************************************
//
// �p�X����t�@�C�������擾
//
//*****************************************************************************
wstring pathToFileName(const wstring path)
{
	wstring fileName = path.substr(path.find_last_of(L'\\') + 1, path.find_first_of(L'.'));		// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	fileName = fileName.substr(0, fileName.find_first_of(L'.'));								// exp: ccc.fbx -> ccc

	return fileName;
}