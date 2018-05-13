//*****************************************************************************
//
// エンジンコアファイル [Engine.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine.h"

//*****************************************************************************
//
// wstring(unicode) to string(unicode)
//
//*****************************************************************************
string wStringToString(const wstring& ws)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const wchar_t* wchSrc = ws.c_str();
	size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
	char *chDest = new char[nDestSize];
	memset(chDest, 0, nDestSize);
	wcstombs(chDest, wchSrc, nDestSize);
	std::string strResult = chDest;
	delete[]chDest;
	setlocale(LC_ALL, strLocale.c_str());
	return strResult;
}

//*****************************************************************************
//
// string(unicode) to wstring(unicode)
//
//*****************************************************************************
wstring stringToWString(const string& s)
{
	std::string strLocale = setlocale(LC_ALL, "");
	const char* chSrc = s.c_str();
	size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
	wchar_t* wchDest = new wchar_t[nDestSize];
	wmemset(wchDest, 0, nDestSize);
	mbstowcs(wchDest, chSrc, nDestSize);
	std::wstring wstrResult = wchDest;
	delete[]wchDest;
	setlocale(LC_ALL, strLocale.c_str());
	return wstrResult;
}

//*****************************************************************************
//
// パスからファイル名を取得
//
//*****************************************************************************
wstring pathToFileName(const wstring path)
{
	wstring fileName = path.substr(path.find_last_of(L'\\') + 1, path.find_first_of(L'.'));		// exp: c:/aaa/bbb/ccc.fbx -> ccc.x
	fileName = fileName.substr(0, fileName.find_first_of(L'.'));								// exp: ccc.fbx -> ccc

	return fileName;
}

//*****************************************************************************
//
// string(UTF-8) to wstring(Unicode)
//
//*****************************************************************************
wstring stringUTF8ToUnicode(const string& s)
{
	int len = s.length();
	int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, (LPWSTR)pUnicode, unicodeLen);
	wstring rt;
	rt = (wchar_t*)pUnicode;
	delete pUnicode;

	return rt;
}

//*****************************************************************************
//
// wstring(Unicode) to string(UTF-8)
//
//*****************************************************************************
string wstringUnicodeToUTF8(const wstring& ws)
{
	char* elementText;
	int textLen;
	// wide char to multi char
	textLen = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);
	elementText = new char[textLen + 1];
	memset((void*)elementText, 0, sizeof(char)*(textLen + 1));
	WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, elementText, textLen, NULL, NULL);
	string str;
	str = elementText;
	delete[] elementText;
	return str;
}