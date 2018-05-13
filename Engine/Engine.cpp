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
// wstring to string
//
//*****************************************************************************
string WStringToString(const wstring& ws)
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
// string to wstring
//
//*****************************************************************************
wstring StringToWString(const string& s)
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